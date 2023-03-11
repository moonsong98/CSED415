# Task 1

By using frequency analyasis(especially single frequency, bigram frequency, trigram frequency), I figured out that the decryption key is like below

|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|y|i|m|j|t|h|e|g|n|l|p|a|c|z|u|o|w|v|q|f|r|b|k|x|d|s|

## Commmand

```
tr 'abcdefghijklmnopqrstuvwxyz' 'yimjthegnlpaczuowvqfrbkxds' < ciphertext.txt > plaintext.txt
```

