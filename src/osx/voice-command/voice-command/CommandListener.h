#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#import "CommandReporter.h"

@interface CommandListener : NSObject<NSSpeechRecognizerDelegate> {
    NSSpeechRecognizer *listen;
    id<CommandReporter> reporter;
}

- (id)init;
- (void)listenFor:(NSArray *)cmds withReporter:(id<CommandReporter>)aReporter;

@end