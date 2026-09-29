Name: show
Version: 1.0
Release: alt
Summary: show binary
Group: show tool
Source: %name-%version.tar.gz
License: Unspecified

%description
build binary and install to buildroot

%prep
%setup -n show

%build
make

%install
make install DESTDIR=%buildroot

%files
/usr/bin/Show
