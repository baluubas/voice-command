#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#import "CommandListener.h"

@implementation CommandListener

-(id)init {
    listen = [[NSSpeechRecognizer alloc] init];
    [listen setDelegate:self];
    [listen setListensInForegroundOnly:NO];
    [listen setBlocksOtherRecognizers:YES];
    return self;
}

-(void)listenFor:(NSArray *)cmds withReporter:(id<CommandReporter>)aReporter {
    reporter = aReporter;
    [listen setCommands:cmds];
    [listen startListening];
}

- (void)speechRecognizer:(NSSpeechRecognizer *)sender didRecognizeCommand:(id)aCmd {
    [reporter onCommand:aCmd];
}


@end