#import <Cocoa/Cocoa.h>

@interface Speech : NSObject
{
    IBOutlet NSButton *sbListent;
    IBOutlet NSProgressIndicator *statusWheel;
    IBOutlet NSTableView *tblCommands;
    IBOutlet NSTextField *txtRecognizedCommand;
    NSMutableArray *listOfCommands;
    NSSpeechRecognizer *recognize;
}
- (IBAction)btnAdd_Click:(id)sender;
- (IBAction)btnRemove_Click:(id)sender;
- (IBAction)sbListen_Toggle:(id)sender;
@end
