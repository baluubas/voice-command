#import "stdio.h"
#import "StandardOutputReporter.h"

@implementation StandardOutputReporter 

- (void)onCommand:(NSString *)command {
    printf("%s", [command UTF8String]);
    printf("\n");
    fflush(stdout);
}


@end