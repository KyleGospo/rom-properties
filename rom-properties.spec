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
Recommends:     lz4
Recommends:     lzo

BuildRequires:  systemd-rpm-macros
BuildRequires:  cmake
BuildRequires:  gcc
BuildRequires:  g++
BuildRequires:  pkgconf
BuildRequires:  gettext
BuildRequires:  libseccomp-devel
BuildRequires:  curl-devel
BuildRequires:  zlib-devel
BuildRequires:  lz4-devel
BuildRequires:  lzo-devel
BuildRequires:  tinyxml2-devel
BuildRequires:  libpng-devel
BuildRequires:  libjpeg-turbo-devel

%global debug_package %{nil}

%description
This shell extension adds a few nice features to file browsers for managing video game ROM and disc images.

%prep
{{{ git_dir_setup_macro }}}

%build
%cmake
%cmake_build

%install
%cmake_install
rm -rf %{buildroot}%{_sysconfdir}/apparmor.d
rm -rf %{buildroot}%{_prefix}/lib/debug

%files
%license %{_defaultdocdir}/%{name}/LICENSE
%doc %{_defaultdocdir}/%{name}/NETWORK.md
%doc %{_defaultdocdir}/%{name}/COMPILING.md
%doc %{_defaultdocdir}/%{name}/README.md
%doc %{_defaultdocdir}/%{name}/NEWS.md
%doc %{_defaultdocdir}/%{name}/keys.conf.example
%doc %{_defaultdocdir}/%{name}/%{name}.conf.example
%{_datadir}/%{name}/amiibo-data.bin
%{_datadir}/applications/com.gerbilsoft.%{name}.rp-config.desktop
%{_datadir}/mime/packages/%{name}.xml
%{_datadir}/metainfo/com.gerbilsoft.%{name}.metainfo.xml
%{_datarootdir}/locale/*/LC_MESSAGES/%{name}.mo
%{_libdir}/libromdata.*
%{_libexecdir}/rp-download
%{_libexecdir}/rp-thumbnail
%{_bindir}/rpcli
%{_bindir}/rp-stub
%{_bindir}/rp-config

%changelog
{{{ git_dir_changelog }}}
