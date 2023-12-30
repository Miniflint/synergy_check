FROM archlinux

RUN pacman -Sy --noconfirm git vim make gcc curl zsh neofetch valgrind lldb

RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

WORKDIR /checking_files  
COPY . . 

ENTRYPOINT [ "zsh" ]