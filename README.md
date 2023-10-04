# leviathan-lisp

按照build-your-own-lisp实现的lisp interpreter.

文章链接：https://www.buildyourownlisp.com/

## Prerequisite
```bash
# Install editline lib(No need for Windows)
# For mac
xcode-select --install
# For Linux(Debian, Ubuntu)
sudo apt-get install libedit-dev
# For Linux(Fedora)
su -c "yum install libedit-dev*"
```

## Compilation
```bash
git clone https://github.com/levia-than/leviathan-lisp.git
cd leviathan-lisp
git submodule init
git submodule update
make
```