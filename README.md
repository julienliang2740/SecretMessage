# SecretMessage

(Current made for messages on a single line, characters between ascii 32-126 inclusive)

Message encoding system (with executables provided)

Encoding example, store the content from ```message.txt``` into ```output.txt```:
```
./encode < message.txt > output.txt
```

Decoding example, check out the secret message stored in ```output.txt```:
```
./decode < output.txt
```