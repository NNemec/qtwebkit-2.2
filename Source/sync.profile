%modules = ( # path to module name map
    "QtWebKit" => "$basedir/WebCore",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
    "QtWebKit" => "../WebKit/qt/Api",
);
%classnames = (
);
%mastercontent = (
    "core" => "#include <QtCore/QtCore>\n",
    "gui" => "#include <QtGui/QtGui>\n",
    "network" => "#include <QtNetwork/QtNetwork>\n",
    "script" => "#include <QtScript/QtScript>\n",
);
%modulepris = (
    "QtWebKit" => "$basedir/WebKit/qt/qt_webkit_version.pri",
);
# Modules and programs, and their dependencies.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - "LATEST_REVISION", to always test against the latest revision.
#   - "LATEST_RELEASE", to always test against the latest public release.
#   - "THIS_REPOSITORY", to indicate that the module is in this repository.
%dependencies = (
    "QtWebKit" => {
        "QtDBus" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "QtXml" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "QtGui" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "QtXmlPatterns" => "26edd6852a62aeec49712a53dcc8d4093192301c",
        "QtNetwork" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "QtCore" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "phonon" => "3c8a216b855d158c48c27e06294226aab611426c",
        "QtDeclarative" => "90ff2cdea3126bdff2746ecf868004711ea628b1",
    },
    "QtWebKit-tests" => {
        "QtWebKit" => "THIS_REPOSITORY",
        "QtDeclarative" => "90ff2cdea3126bdff2746ecf868004711ea628b1",
    },
);
