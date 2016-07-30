//
//  ScreenViewController.m
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 04/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#import <SCLTFramework/Support.h>
#import <SCLTFramework/Rasterizer.h>
#import <SCLTFramework/ViewPlane.hpp>
#import <SCLTFramework/ColorRenderingIndex.hpp>
#import <SCLTFramework/SCLT.hpp>

#import "MainViewController.h"

@interface MainViewController ()

/// Rasterizer reference.
@property (strong, nonatomic) Rasterizer *raster;
/// View used to raster the image obtained.
@property (weak, nonatomic) IBOutlet UIImageView *rasterImageView;
/// Scene identifier.
@property (weak, nonatomic) IBOutlet UITextField *sceneName;
/// Anti-aliasing number of sample.
@property (weak, nonatomic) IBOutlet UITextField *antialiasingNumberOfSample;
/// Progress view.
@property (weak, nonatomic) IBOutlet UIProgressView *progressView;
/// Rendering time label.
@property (weak, nonatomic) IBOutlet UILabel *renderingTimeLabel;
/// Start ray tracing button.
@property (weak, nonatomic) IBOutlet UIButton *startRayTracingButton;

@end

@implementation MainViewController

- (void)viewDidLoad {
    
    //Init the raster.
    self.raster = [[Rasterizer alloc] init];
    
    //Hide UI status.
    self.progressView.alpha = 0.0;
    self.renderingTimeLabel.alpha = 0.0;
}

- (void)showAlert:(NSString *)message withTitle:(NSString *)title {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        //Show CRI
        UIAlertController* alert = [UIAlertController
                                    alertControllerWithTitle:title
                                    message:message
                                    preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction* ok = [UIAlertAction
                             actionWithTitle:@"OK"
                             style:UIAlertActionStyleDefault
                             handler:^(UIAlertAction * action) {
                                 [alert dismissViewControllerAnimated:YES completion:nil];
                             }];
        
        [alert addAction:ok];
        
        [self presentViewController:alert animated:YES completion:nil];
        
    });
}

#pragma mark Ray tracer

- (IBAction)startRayTracingAction:(UIButton *)sender {
    
    //Setup UI
    //- reset rasterImage
    //- disable start ray tracing button
    //- show progressView
    self.rasterImageView.image = nil;
    self.startRayTracingButton.enabled = NO;
    self.startRayTracingButton.alpha = 0.5f;
    self.renderingTimeLabel.alpha = 0.0f;
    self.renderingTimeLabel.text = @"";
    [UIView animateWithDuration:0.5 animations:^{
        self.progressView.alpha = 1.0f;
    }];
    
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
        
        //Init view plane.
        ViewPlane vplane = ViewPlane(600, 600);
        
        //Read scene name and anti aliasing number of sample.
        std::string sceneName([self.sceneName.text UTF8String]);
        
        if(sceneName == "") {
            
            [self showAlert:@"Scene name not valid"
                  withTitle:@"Scene not valid"];
            
            self.startRayTracingButton.enabled = YES;
            self.startRayTracingButton.alpha = 1.0f;
            
            return;
        }
        
        int antialiasingNumOfSample = self.antialiasingNumberOfSample.text.intValue;
        
        //Init ray tracer.
        SCLT scltRayTracer(vplane, sceneName, antialiasingNumOfSample);
        
        std::string sceneErrorsDescription;
        
        //Scene is not valid
        if(!scltRayTracer.validScene(sceneErrorsDescription)) {
            
            NSString *sceneErrorsNSDescription = [NSString stringWithCString:sceneErrorsDescription.c_str()
                                                                    encoding:NSUTF8StringEncoding];
            
            [self showAlert:sceneErrorsNSDescription
                  withTitle:@"Scene not valid"];
            
            self.startRayTracingButton.enabled = YES;
            self.startRayTracingButton.alpha = 1.0f;

            [UIView animateWithDuration:0.5 animations:^{
                
                self.progressView.alpha = 0.0f;
            }];
            
            return;
        }
        
        //Set delegate of the progress bar.
        //CALLED ONLY ON APPLE PLATFORM
        scltRayTracer.setDelegate(self);
        
        //Start time
        NSDate *startDate = [Support currentTime:@"Start"];
        
        //Run ray tracer.
        std::vector<Vector3D> pixels = scltRayTracer.runSCLTRayTracer();
        
        //Generate image.
        UIImage *rasterImage = [self.raster rasterize:pixels andHeight:vplane.height andWidth:vplane.width];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            //Display image.
            self.rasterImageView.image = rasterImage;
            
            //End time.
            NSDate *endDate = [Support currentTime:@"End"];
            
            //Restore UI.
            self.startRayTracingButton.enabled = YES;
            self.startRayTracingButton.alpha = 1.0f;
            [UIView animateWithDuration:0.5 animations:^{
                
                self.progressView.alpha = 0.0f;
            } completion:^(BOOL finished) {
                
                self.progressView.progress = 0.0f;
                
                //Show rendering time.
                [UIView animateWithDuration:0.5 animations:^{
                    
                    NSString *renderingTime = [Support dateDifferenceBetween:startDate
                                                                andStartDate:endDate];
                    self.renderingTimeLabel.text = [NSString stringWithFormat:@"Rendering time: %@", renderingTime];
                    
                    self.renderingTimeLabel.alpha = 1.0;
                }];
            }];
        });
    });
}

#pragma mark CRI

- (IBAction)calibrateCRI:(id)sender {
    
    //Calibrate CRI with f4 illuminant.
    Spectrum<constant::spectrumSamples> spectrumF4(Illuminant::fl4);
    
    //Show CRI.
    [self CRI:spectrumF4];
}

- (IBAction)calculateCRI:(id)sender {
    
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
        
        //Convert NSString name to std::string.
        std::string sceneName([self.sceneName.text UTF8String]);
        
        //Init scene.
        Scene sceneSelected(sceneName);
        
        //Check if we can calculate the CRI for the selected scene.
        if (sceneSelected.tracerModelType == TracerRGBModel) {
            
            [self showAlert:@"CRI not available for a RGB scene."
                  withTitle:@"Color Rendering Index"];
            
            return;
        }
        
        //Calculate CRI for the scene light.
        [self CRI:sceneSelected.originalLightSpectrum];
    });
}

- (void)CRI:(Spectrum<constant::spectrumSamples>)light {
    
    ColorRenderingIndex cri;
    float criTestSample = cri.testSampleMethod(light);
    float criR96a = cri.r96aMethod(light);
    
    [self showAlert:[NSString stringWithFormat: @"Test sample method: %f\nR96a: %f", criTestSample, criR96a]
          withTitle:@"Color Rendering Index"];
}

#pragma mark Progress Bar Update

- (void)rayTracerProgressUpdate:(float)progress {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        //Update progress bar status.
        //Dispatched on main queue (UI Thread).
        self.progressView.progress = progress;
    });
}

#pragma mark UITextField delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    
    [textField resignFirstResponder];
    return NO;
}

@end
