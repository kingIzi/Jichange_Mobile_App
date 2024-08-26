cmake_minimum_required(VERSION 3.16)

project(jichange_v3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Felgo REQUIRED)
find_package(Qt6 COMPONENTS REQUIRED Charts NetworkAuth Svg WebView Network LinguistTools Concurrent)


# Project identifier and version
# More information: https://felgo.com/doc/felgo-publishing/#project-configuration
set(PRODUCT_IDENTIFIER "com.yourcompany.wizardEVAP.Jichangev3")
set(PRODUCT_VERSION_NAME "1.0.0")
set(PRODUCT_VERSION_CODE 1)

# Set either "test" or "publish" stage:
set(PRODUCT_STAGE "test")
set(CLIENT_SECRET_CONFIGURATION "${PROJECT_SOURCE_DIR}/assets/credentials/client_secret.json")

# Optionally set a license key that is used instead of the license key from
# main.qml file (App::licenseKey for your app or GameWindow::licenseKey for your game)
# Only used for local builds and Felgo Cloud Builds (https://felgo.com/cloud-builds)
# Not used if using Felgo Live
set(PRODUCT_LICENSE_KEY "")

set(FELGO_PLUGINS
)

# Find all QML/JS files for the QML compiler:
file(GLOB_RECURSE QmlFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} qml/*.qml qml/*.js)

# Find all non-QML/JS files in the qml and assets folder to add as resources:
file(GLOB_RECURSE AssetsFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} assets/* qml/*)
list(REMOVE_ITEM AssetsFiles ${QmlFiles})

include_directories(include/)

qt_add_executable(appjichange_v3
    src/main.cpp
    ${QmlFiles}
    ${AssetsFiles}
)

set(CPP_FILES
    src/requests/requests.cpp
    src/requests/authrequests.cpp
    src/requests/setupbranch.cpp
    src/requests/setuprequests.cpp
    src/requests/companyusersrequests.cpp
    src/requests/invoicerequests.cpp

    src/latesttransactionstablemodel.cpp
    src/customerstablemodel.cpp

    src/forms/vendorregistrationform.cpp
    src/forms/companyuserform.cpp
    src/forms/formvalidator.cpp
    src/forms/customerform.cpp
    src/forms/vendorreportform.cpp
    src/forms/invoiceform.cpp

    src/models/branchlistmodel.cpp
    src/models/branchlistitems.cpp

    src/entities/branch.cpp
    src/entities/companyuser.cpp
)

set(HEADER_FILES
    include/requests/companyusersrequests.h
    include/requests/requests.h
    include/requests/authrequests.h
    include/requests/setupbranch.h
    include/requests/setuprequests.h
    include/requests/invoicerequests.h

    include/customerstablemodel.h
    include/latesttransactionstablemodel.h

    include/forms/vendorregistrationform.h
    include/forms/companyuserform.h
    include/forms/formvalidator.h
    include/forms/customerform.h
    include/forms/vendorreportform.h
    include/forms/invoiceform.h

    include/models/branchlistitems.h
    include/models/branchlistmodel.h

    include/entities/branch.h
    include/entities/companyuser.h
)

add_library(sources_test ${CPP_FILES} ${HEADER_FILES})


if (WIN32)
    add_subdirectory(testing)
    #add_subdirectory(tests)
endif()

felgo_configure_executable(appjichange_v3)

# Deploy resources to build folder/package directly
# comment for publishing
deploy_resources("${QmlFiles};${AssetsFiles}")

# Add QML files and resources to QML module to included them via QRC automatically:
qt_add_qml_module(appjichange_v3
    URI jichange_v3
    VERSION 1.0
# uncomment for publishing:
    QML_FILES ${QmlFiles}
    RESOURCES ${AssetsFiles}
#    NO_RESOURCE_TARGET_PATH
)

# NOTE: for PUBLISHING, perform the following steps:
# 1. comment the deploy_resources line above, to avoid shipping your qml files with the application (instead they get compiled to the app binary)
# 2. uncomment the QML_FILES and RESOURCES above; this compiles your qml files and js files to the app binary and protects your source code
# 3. change the setMainQmlFile() call in main.cpp to the one starting with "qrc:/" - this loads the qml files from the resources
# for more details see the "Deployment Guides" in the Felgo Documentation

# during development, use the deploy_resources because you then get shorter compilation times (the qml files do not need to be compiled to the binary but are just copied)
# also, for quickest deployment on Desktop disable the "Shadow Build" option in Projects/Builds - you can then select "Run Without Deployment" from the Build menu in Qt Creator if you only changed QML files; this speeds up application start, because your app is not copied & re-compiled but just re-interpreted

target_compile_definitions(appjichange_v3
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)


target_link_libraries(sources_test PUBLIC Qt6::Core Qt::Gui Qt6::Charts Qt6::Qml Qt6::Quick Qt6::Network Qt6::NetworkAuth Qt6::WebView Qt6::Network Qt6::Svg Qt6::Concurrent)
target_compile_definitions(sources_test PRIVATE  CLIENT_SECRET_CONFIGURATION="${CLIENT_SECRET_CONFIGURATION}")


target_link_libraries(appjichange_v3 PRIVATE Felgo sources_test)

# uncomment this line to add the Live Client Module and use live reloading with your custom C++ code
# for the remaining steps to build a custom Live Code Reload app see here: https://felgo.com/custom-code-reload-app/
find_package(FelgoLive REQUIRED)
target_link_libraries(appjichange_v3 PRIVATE FelgoLive sources_test)
#if (ANDROID)
#    include(C:/Users/scott/AppData/Local/Android/Sdk/android_openssl/CMakeLists.txt)
#endif()
