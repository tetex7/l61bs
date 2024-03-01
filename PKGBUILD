 # Maintainer: tete <tetex7@outlook.com>
pkgname=l61
pkgver=2.2.0
pkgrel=1
pkgdesc='the λ61 build system'
url='https://github.com/tetex7/l61bs'
#source=("$pkgname-$pkgver.tar.gz::https://github.com/Morganamilo/paru/archive/v$pkgver.tar.gz")
#backup=("etc/paru.conf")
provides=('l61' 'mk61')
arch=('x86_64')
PACKAGER="TRS"
license=('GPL3')
makedepends=('boost' 'lua')
depends=('boost-libs' 'lua')

prepare() {
cd ..
echo $PWD
#make clean
}

build () {
    cd ..
    echo $PWD
    make
    make pak
}

package() {
  #cd "$srcdir/$pkgname-$pkgver"
    cd ..
    cd ./l61
    echo $PWD
  #fs/l61confg.conf61
    libf=$(ls ./lib)
    install -Dm644 ./l61confg.conf61 "${pkgdir}/etc/l61confg.conf61"
    install -Dm644 ./stup/l61.lua "${pkgdir}/opt/l61/stup/l61.lua"
    install -Dm644 ./LICENSE "${pkgdir}/opt/l61/LICENSE"
    install -Dm644 ./boot.lua "${pkgdir}/opt/l61/boot.lua"
    cp -ar ./prefrom_l61 "${pkgdir}/opt/l61/prefrom_l61"
    for item in ${libf}; do
      install -Dm644 ./lib/${item} "${pkgdir}/opt/l61/lib/${item}"
    done
    mkdir  "${pkgdir}/usr"
    mkdir  "${pkgdir}/usr/bin"
    cp -ar ./l61 "${pkgdir}/usr/bin/l61"
    cp -ar ./mk61 "${pkgdir}/usr/bin/mk61"
    install -Dm755 ./bin/l61 "${pkgdir}/opt/l61/bin/l61"
    install -Dm755 ./KROM.sh "${pkgdir}/opt/l61/KROM.sh"

    
    #ln --relative -s "./opt/l61/bin/l61" "./usr/bin/l61"
    #ln --relative -s "./opt/l61/bin/mk61" "./usr/bin/mk61"
}

