#
# Conditional build:
%bcond_without	apidocs		# do not build and package API docs
#
%define ver	%(echo %{version} | tr . _)
Summary:	library for generating PDF documents
Summary(pl.UTF-8):	biblioteka do generowania dokumentów PDF
Name:		libharu
Version:	2.0.8
Release:	3
License:	distributable
Group:		Libraries
Source0:	http://dl.sourceforge.net/libharu/%{name}_%{ver}.tgz
# Source0-md5:	4b9714fd89b4134b0b9c93f857add327
Patch0:		%{name}-destdir.patch
URL:		http://libharu.org/
BuildRequires:	libpng-devel
BuildRequires:	zlib-devel
BuildRoot:	%{tmpdir}/%{name}-%{version}-root-%(id -u -n)

%description
HARU is a free, cross platform, open-sourced software library for
generating PDF. It supports the following features:
- Generating PDF files with lines, text, images.
- Outline, text annotation, link annotation.
- Compressing document with deflate-decode.
- Embedding PNG, Jpeg images.
- Embedding Type1 font and TrueType font.
- Creating encrypted PDF files.
- Using various character set (ISO8859-1~16, MSCP1250~8, KOI-8R).
- Supporting CJK fonts and encodings.

You can add the feature of PDF creation by using HARU without
understanding complicated internal structure of PDF.

%description -l pl.UTF-8
HARU to darmowa, dostepna na wiele platform biblioteka open source do
generowania dokumentów PDF. Biblioteka ta umożliwia:
- generowanie dokumentów PDF z liniami, tekstem czy obrazkami,
- oznaczanie tekstu i odnośników,
- kompresję dokumentu za pomocą deflate-decode,
- osadzanie obrazków PNG i JPEG,
- osadzanie czcionek Type1 i TrueType,
- tworzenie zaszyforwanie dokumentów PDF,
- wsparcie dla różnych zestawów znaków (ISO8859-1~16 MSCP1250~8,
  KOI-8R),
- wsparcie dla czcionek i kodowań znaków CJK.

%package devel
Summary:	Header files for haru library
Summary(pl.UTF-8):	Pliki nagłówkowe biblioteki haru
Group:		Development/Libraries
Requires:	%{name} = %{version}-%{release}

%description devel
Header files for haru library.

%description devel -l pl.UTF-8
Pliki nagłówkowe biblioteki haru.

%prep
%setup -q
%patch0 -p1

%build
./configure \
	--shared \
	--prefix=%{_prefix} \
	--cflags="%{rpmcflags}"
%{__make} \
	CC="%{__cc}"

%install
rm -rf $RPM_BUILD_ROOT

%{__make} install \
	PREFIX=%{_prefix} \
	LIBDIR=%{_libdir} \
	DESTDIR=$RPM_BUILD_ROOT

install include/* $RPM_BUILD_ROOT%{_includedir}

%clean
rm -rf $RPM_BUILD_ROOT

%post	-p /sbin/ldconfig
%postun	-p /sbin/ldconfig

%files
%defattr(644,root,root,755)
%doc README TODO
%attr(755,root,root) %{_libdir}/lib*.so.*.*.*

%files devel
%defattr(644,root,root,755)
%{_libdir}/lib*.so
%{_includedir}/*
