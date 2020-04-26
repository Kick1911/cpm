
#!/usr/bin/bash
export _CONFIG_INSTALL_PATH=\"/usr/local/\"

for arg in \"$@\"; do
    if [[ $arg =~ --prefix=(.+) ]];then
        _CONFIG_INSTALL_PATH=\"${BASH_REMATCH[1]}\"
    fi
done

echo '' >> Makefile.in
if [[ `command -v gcc` ]]; then
    echo 'gcc found'
elif [[ `command -v clang` ]]; then
    echo 'clang found'
else
    echo 'Compatible C compiler not found.'
    exit 1
fi

echo '' > Makefile.in
for x in `env | grep \"^_CONFIG_\"`; do
    echo \"$x\" >> Makefile.in
done

