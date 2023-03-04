CLANG_FORMAT=clang-format-10

if [ -x "$(command -v clang-format-10)" ]; then
    CLANG_FORMAT=clang-format-10
elif [ -x "$(command -v clang-format)" ]; then
    echo "clang-format might be different from clang-format-10, expect potential difference."
    CLANG_FORMAT=clang-format
else
    echo "Cannot find clang-format-10"
    exit 1
fi

if [ "$1" == "--check-only" ]
then
    echo "Running Clang-Format (Check Only)"
    find src/ -type f \( -name '*.h' -or -name '*.cc' \) -print | xargs $CLANG_FORMAT --sort-includes -i --dry-run -Werror
else
    echo "Running Clang-Format With modifying the source code"
    find src/ -type f \( -name '*.h' -or -name '*.cc' \) -print | xargs $CLANG_FORMAT --sort-includes -i
fi
