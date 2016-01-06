var addon = require('./build/Release/vntoken.node')
var test = new addon.NodeToken('hello')

console.log(addon.NodeToken)

test.add('!')

console.log(test.toString())
