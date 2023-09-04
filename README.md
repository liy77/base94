# Base94

## Installation
```bash
npm install base94
```

### Using PNPM
```bash
pnpm add base94
```

## How to use
```js
const base94 = require("base94");

const original = "Hello, World!";
const encoded = base94(original);

console.log("Encoded:", encoded); // Output: Ifmmp-!Xpsme"
console.log("Decoded:", base94.decode(encoded)); // Output: Hello, World!
```