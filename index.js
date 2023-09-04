const __base94__ = require("./build/Release/base94.node");

function base94(str) {
    return __base94__.encode(str);
}

base94.encode = __base94__.encode;
base94.decode = __base94__.decode;

module.exports = base94;
