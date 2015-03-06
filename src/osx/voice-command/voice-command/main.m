#import <stdio.h>

#import <CoreFoundation/CoreFoundation.h>
#import <Foundation/Foundation.h>

#import "StandardOutputReporter.h"
#import "CommandListener.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: hotword phrase [<phrase> ...]\n");
        return 1;
    }
    
    @autoreleasepool {
        NSArray *args = [[NSProcessInfo processInfo] arguments];
        NSArray *cmds = [args subarrayWithRange: NSMakeRange( 1, argc-1)];
        
        CommandListener *cmdListener = [[CommandListener alloc] init];
        id<CommandReporter> cmdReporter = [StandardOutputReporter alloc];
        
        [cmdListener listenFor:cmds withReporter:cmdReporter];
        CFRunLoopRun();
    }
    return  0;
}