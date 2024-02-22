SUMMARY = "Simple helloworld application"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/agent/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://agent/"

S = "${WORKDIR}/agent"
#do_compile() {
#    echo "Compiling agent"
#    ${CC} ${LDFLAGS} agent.cpp -o agent
#}
#do_install() {
#    echo "Installing agent"
#    install -d ${D}${bindir}
#    install -m 0755 agent ${D}${bindir}
#}

#inherit npm

#do_install() {
#    oe_runmake install DESTDIR=${D}
#}

#FILES_${PN} += "${bindir}/agent"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/agent.sh ${D}${bindir}/agent
}

FILES_${PN} += "${bindir}/agent"
