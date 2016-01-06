var addon = require('./build/Release/addon')
var test = new addon.NodeToken('test')

test.add('!')
console.log("test's contents: %s", test)
