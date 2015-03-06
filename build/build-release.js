
var os 		= require('os');
	spawn 	= require('child_process').spawn;

var platform = os.platform();
if(platform === 'darwin') {
	var child = spawn('xcodebuild', {
		cwd: 'src/osx/voice-command/'
	});
}
else {
	throw new Exception('Platform ' + platform + ' is not supported yet.');
}

child.on('close', function(code) {
  if (code !== 0) {
    console.log('Build process exited with code ' + code);
	process.exit(1);    
  }
});