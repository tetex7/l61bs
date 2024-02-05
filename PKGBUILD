 # Maintainer: tete <tetex7@outlook.com>
pkgname=l61
pkgver=2.2.0_dev
pkgrel=1
pkgdesc='the λ61 build system'
url='https://github.com/tetex7/l61bs'
#source=("$pkgname-$pkgver.tar.gz::https://github.com/Morganamilo/paru/archive/v$pkgver.tar.gz")
#backup=("etc/paru.conf")
arch=('x86_64')
license=('GPL3')
makedepends=('boost' 'lua')
depends=('boost-libs' 'lua')
##optdepends=('bat: colored pkgbuild printing' 'devtools: build in chroot and downloading pkgbuilds')
#sha256sums=('63cba8f64f04ab6bfab5630a6a269a333a1ac0260ac1715f836f31cf9327e26f')

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
    libf=$(ls ./lib)
    install -Dm644 ./stup/l61.lua "${pkgdir}/opt/l61/stup/l61.lua"
    install -Dm644 ./boot.lua "${pkgdir}/opt/l61/boot.lua"
    cp -ar ./prefrom_l61 "${pkgdir}/opt/l61/prefrom_l61"

    for item in ${libf}; do
      install -Dm644 ./lib/${item} "${pkgdir}/opt/l61/lib/${item}"
    done
    
    install -Dm755 ./bin/l61 "${pkgdir}/opt/l61/bin/l61"
    install -Dm755 ./bin/mk61 "${pkgdir}/opt/l61/bin/mk61"
    install -Dm755 ./KROM.sh "${pkgdir}/opt/l61/KROM.sh"
}

