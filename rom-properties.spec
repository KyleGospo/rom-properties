Name:           rom-properties
Version:        {{{ git_dir_version }}}
Release:        1%{?dist}
Summary:        File browser extension for managing video game ROM and disc images
License:        GPLv2
URL:            https://github.com/KyleGospo/%{name}

VCS:            {{{ git_dir_vcs }}}
Source:         {{{ git_dir_pack }}}

Requires:       curl
Requires:       zlib
Requires:       libpng
Requires:       libjpeg-turbo
Requires:       nettle
Requires:       tinyxml2
Requires:       libseccomp
Requires:       %{name}-common = %{version}-%{release}
Requires:       %{name}-thumbnailer-dbus = %{version}-%{release}
Requires:       %{name}-utils = %{version}-%{release}
Recommends:     lz4
Recommends:     lzo

BuildRequires:  systemd-rpm-macros
BuildRequires:  cmake
BuildRequires:  gcc
BuildRequires:  g++
BuildRequires:  pkgconf
BuildRequires:  gettext-devel
BuildRequires:  libseccomp-devel
BuildRequires:  libcurl-devel
BuildRequires:  nettle-devel
BuildRequires:  zlib-devel
BuildRequires:  lz4-devel
BuildRequires:  lzo-devel
BuildRequires:  libzstd-devel
BuildRequires:  tinyxml2-devel
BuildRequires:  libpng-devel
BuildRequires:  libjpeg-turbo-devel
BuildRequires:  gsound-devel
BuildRequires:  qt5-qtbase-devel
BuildRequires:  qt5-qttools
BuildRequires:  extra-cmake-modules
BuildRequires:  kf5-kio-devel
BuildRequires:  kf5-kwidgetsaddons-devel
BuildRequires:  kf5-kfilemetadata-devel
BuildRequires:  glib2-devel
BuildRequires:  gtk4-devel
BuildRequires:  gdk-pixbuf2-devel
BuildRequires:  nautilus-devel
BuildRequires:  gsound-devel

%global debug_package %{nil}

%description
This shell extension adds a few nice features to file browsers for managing video game ROM and disc images.

%prep
{{{ git_dir_setup_macro }}}
sed -i 's|ENABLE_TESTING()|# ENABLE_TESTING()|g' CMakeLists.txt

%build
%cmake
%cmake_build

%install
%cmake_install
kbuildsycoca5 --noincremental
rm -rf %{buildroot}%{_sysconfdir}/apparmor.d
rm -rf %{buildroot}%{_prefix}/lib/debug
rm %{buildroot}%{_libdir}/thunarx-2/rom-properties-xfce.so

%files
%license %{_defaultdocdir}/%{name}/LICENSE
%doc %{_defaultdocdir}/%{name}/NETWORK.md
%doc %{_defaultdocdir}/%{name}/COMPILING.md
%doc %{_defaultdocdir}/%{name}/README.md
%doc %{_defaultdocdir}/%{name}/NEWS.md
%doc %{_defaultdocdir}/%{name}/keys.conf.example
%doc %{_defaultdocdir}/%{name}/rom-properties.conf.example
%{_libdir}/libromdata.*

%package cli
Summary: CLI tools for rom-properties
Requires: %{name}%{?_isa} = %{version}-%{release}

%description cli
%{summary}

%files cli
%{_bindir}/rpcli

%package common
Summary: Common files for rom-properties
Requires: %{name}%{?_isa} = %{version}-%{release}
BuildArch: noarch

%description common
%{summary}

%files common
%{_datadir}/%{name}/amiibo-data.bin
%{_datadir}/applications/com.gerbilsoft.rom-properties.rp-config.desktop
%{_datadir}/metainfo/com.gerbilsoft.rom-properties.metainfo.xml
%{_datadir}/mime/packages/rom-properties.xml
%{_datarootdir}/locale/*/LC_MESSAGES/rom-properties.mo

%package gtk3
Summary: GTK3/4 integration for rom-properties
Requires: %{name}%{?_isa} = %{version}-%{release}

%description gtk3
%{summary}

%files gtk3
%{_libdir}/nautilus/extensions-3.0/rom-properties-gtk3.so
%{_libdir}/nautilus/extensions-4/rom-properties-gtk4.so
%{_libdir}/caja/extensions-2.0/rom-properties-gtk3.so
%{_libdir}/nemo/extensions-3.0/rom-properties-gtk3.so
%{_libdir}/thunarx-3/rom-properties-gtk3.so

%package kf5
Summary: KDE5 integration for rom-properties
Requires: %{name}%{?_isa} = %{version}-%{release}

%description kf5
%{summary}

%files kf5
%{_datadir}/kio/servicemenus/rp-convert-to-png.desktop
%{_libdir}/qt5/plugins/kf5/thumbcreator/rom-properties-kf5.so
%{_libdir}/qt5/plugins/kf5/propertiesdialog/xattrview-kf5.so
%{_libdir}/qt5/plugins/kf5/kfilemetadata/kfilemetadata_rom-properties-kf5.so
%{_libdir}/qt5/plugins/kf5/overlayicon/overlayiconplugin_rom-properties-kf5.so
%{_libdir}/qt5/plugins/kf5/propertiesdialog/rom-properties-kf5.so

%package thumbnailer-dbus
Summary: Dbus service for rom-properties
Requires: %{name}%{?_isa} = %{version}-%{release}

%description thumbnailer-dbus
%{summary}

%files thumbnailer-dbus
%{_bindir}/rp-thumbnailer-dbus
%{_datadir}/dbus-1/services/com.gerbilsoft.rom-properties.SpecializedThumbnailer1.service
%{_datadir}/thumbnailers/com.gerbilsoft.rom-properties.SpecializedThumbnailer1.service

%package utils
Summary: utils for rom-properties
Requires: %{name}%{?_isa} = %{version}-%{release}

%description utils
%{summary}

%files utils
%{_libexecdir}/rp-download
%{_libexecdir}/rp-thumbnail
%{_datadir}/thumbnailers/rom-properties.thumbnailer
%{_bindir}/rp-stub
%{_bindir}/rp-config

%changelog
{{{ git_dir_changelog }}}
