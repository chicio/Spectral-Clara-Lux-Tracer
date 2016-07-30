//
//  MainViewController.m
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include <CoreServices/CoreServices.h>
#include <Carbon/Carbon.h>

#import <SCLTFramework/SCLT.hpp>
#import <SCLTFramework/Support.h>
#import <SCLTFramework/Rasterizer.h>
#import <SCLTFramework/ViewPlane.hpp>
#import <SCLTFramework/ColorRenderingIndex.hpp>

#import "MainViewController.h"

@interface MainViewController ()

/// Rasterizer reference.
@property (strong, nonatomic) Rasterizer *raster;
/// View used to raster the image obtained.
@property (weak) IBOutlet NSImageView *rasterImageView;
/// Scene identifier.
@property (weak) IBOutlet NSTextField *sceneName;
/// Anti-aliasing number of sample.
@property (weak) IBOutlet NSTextField *antialiasingNumberOfSample;
/// Progress indicator.
@property (weak) IBOutlet NSProgressIndicator *progressIndicator;
/// Start ray tracing button.
@property (weak) IBOutlet NSButton *startRayTracingButton;

@end

@implementation MainViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    //Init the raster.
    self.raster = [[Rasterizer alloc] init];
    
    //Setup UI.
    self.rasterImageView.wantsLayer = YES;
    self.rasterImageView.layer.backgroundColor = [NSColor redColor].CGColor;
    self.progressIndicator.hidden = YES;
}

- (void)setRepresentedObject:(id)representedObject {
    
    [super setRepresentedObject:representedObject];
    // Update the view, if already loaded.
}

- (void)showAlert:(NSString *)message withTitle:(NSString *)title {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle:@"ok"];
        [alert setMessageText:title];
        [alert setInformativeText:message];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
    });
}

#pragma mark Ray tracer

- (IBAction)startRayTracingAction:(id)sender {
    
    //Setup UI
    //- reset rasterImage
    //- disable start ray tracing button
    //- show progressView
    self.rasterImageView.image = nil;
    self.startRayTracingButton.enabled = NO;
    self.progressIndicator.doubleValue = 0.0;
    self.progressIndicator.hidden = NO;
    
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INTERACTIVE, 0), ^{
        
        //Init view plane.
        ViewPlane vplane = ViewPlane(600, 600);
        
        //Read scene name and anti aliasing number of sample.
        std::string sceneName([[self.sceneName stringValue] UTF8String]);
        
        if(sceneName == "") {
            
            [self showAlert:@"Scene name not valid."
                  withTitle:@"Scene not valid"];
            
            self.startRayTracingButton.enabled = YES;
            
            return;
        }
        
        int antialiasingNumOfSample = [self.antialiasingNumberOfSample intValue];
        
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
            self.progressIndicator.hidden = YES;

            return;
        }
        
        //Set delegate of the progress bar.
        scltRayTracer.setDelegate(self);
        
        //Start time
        NSDate *startDate = [Support currentTime:@"Start"];
        
        //Run ray tracer.
        std::vector<Vector3D> pixels = scltRayTracer.runSCLTRayTracer();
        
        //Generate image.
        NSImage *rasterImage = [self.raster rasterize:pixels andHeight:vplane.height andWidth:vplane.width];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            self.progressIndicator.hidden = YES;
            
            //Display image.
            self.rasterImageView.image = rasterImage;
            
            //End time.
            NSDate *endDate = [Support currentTime:@"End"];
            
            self.startRayTracingButton.enabled = YES;
            NSString *renderingTime = [Support dateDifferenceBetween:startDate
                                                        andStartDate:endDate];
            
            [self showAlert:renderingTime withTitle:@"Rendering time"];
            
            //macGoesToSleep();
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
    
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INTERACTIVE, 0), ^{
        
        //Convert NSString name to std::string.
        std::string sceneName([[self.sceneName stringValue] UTF8String]);
        
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
        
        //Update progress bar.
        //Dispatched on main queue (UI Thread).
        self.progressIndicator.doubleValue = progress;
    });
}

#pragma mark OS X status

OSStatus macGoesToSleep() {
    
    AEAddressDesc targetDesc;
    static const ProcessSerialNumber kPSNOfSystemProcess = { 0, kSystemProcess };
    AppleEvent eventReply = {typeNull, NULL};
    AppleEvent appleEventToSend = {typeNull, NULL};
    
    OSStatus error = noErr;
    
    error = AECreateDesc(typeProcessSerialNumber, &kPSNOfSystemProcess,
                         sizeof(kPSNOfSystemProcess), &targetDesc);
    
    if (error != noErr) {
        
        return(error);
    }
    
    error = AECreateAppleEvent(kCoreEventClass, kAESleep, &targetDesc,
                               kAutoGenerateReturnID, kAnyTransactionID, &appleEventToSend);
    
    AEDisposeDesc(&targetDesc);
    if (error != noErr) {
        
        return(error);
    }
    
    error = AESend(&appleEventToSend, &eventReply, kAENoReply,
                   kAENormalPriority, kAEDefaultTimeout, NULL, NULL);
    
    AEDisposeDesc(&appleEventToSend);
    if (error != noErr) {
        
        return(error);
    }
    
    AEDisposeDesc(&eventReply);
    
    return(error);
}

@end
