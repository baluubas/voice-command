
var os = require('os'),
	fs = require('fs'),
	spawn 	= require('child_process').spawn;


var platform = os.platform();
console.log(platform);
if(platform === 'darwin') {
	var child = spawn('xcodebuild', {
		cwd: 'src/osx/voice-command/'
	});
}
else if (platform == "win32") {
	var msbuild = 'C:/Windows/Microsoft.NET/Framework64/v4.0.30319/msbuild.exe';
	var child = spawn(msbuild, ['/p:Configuration=Release', 'voice-command.csproj'], {
		cwd: 'src/win/voice-command/'
	});
	child.stdout.on('data', function (data) { console.log('' + data); });
	child.stderr.on('data', function (data) { console.log('' + data); });
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