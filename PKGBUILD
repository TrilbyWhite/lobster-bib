# Maintainer: Jesse McClure AKA "Trilby" <jmcclure [at] cns [dot] umass [dot] edu>
_gitname="lobster-bib"
pkgname="${_gitname}-git"
pkgver=0
pkgrel=1
pkgdesc="CLI Frontend to btparse"
url="http://github.com/TrilbyWhite/lobster-bib.git"
arch=('any')
license=('GPLv2')
depends=('btparse')
makedepends=('git')
source=("${_gitname}::git://github.com/TrilbyWhite/lobster-bib.git")
sha256sums=('SKIP')

pkgver() {
	cd "${_gitname}";
	echo "0.$(git rev-list --count HEAD).$(git describe --always )"
}

build() {
	cd "${_gitname}"
	make
}

package() {
	cd "${_gitname}"
	make PREFIX=/usr DESTDIR="${pkgdir}" install
}
