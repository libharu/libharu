Summary:	Library for generating PDF documents
Summary(pl.UTF-8):	Biblioteka do generowania dokumentów PDF
Name:		libharu
Version:	2.2.1
Release:	1
License:	MIT-like
Group:		Libraries
Source0:	http://libharu.org/files/%{name}-%{version}.tar.bz2
# Source0-md5:	4febd7e677b1c5d54db59a608b84e79f
Patch0:		%{name}-libdir.patch
URL:		http://libharu.org/
BuildRequires:	autoconf >= 2.60
BuildRequires:	automake
BuildRequires:	libpng-devel
BuildRequires:	libtool
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
Summary:	Header files for Haru PDF library
Summary(pl.UTF-8):	Pliki nagłówkowe biblioteki Haru PDF
Group:		Development/Libraries
Requires:	%{name} = %{version}-%{release}

%description devel
Header files for Haru PDF library.

%description devel -l pl.UTF-8
Pliki nagłówkowe biblioteki Haru PDF.

%package static
Summary:	Static Haru PDF library
Summary(pl.UTF-8):	Statyczna biblioteka Haru PDF
Group:		Development/Libraries
Requires:	%{name}-devel = %{version}-%{release}

%description static
Static Haru PDF library.

%description static -l pl.UTF-8
Statyczna biblioteka Haru PDF.

%prep
%setup -q
%patch0 -p1

%build
%{__libtoolize}
%{__aclocal}
%{__autoconf}
%{__autoheader}
%{__automake}
%configure

%{__make}

%install
rm -rf $RPM_BUILD_ROOT

%{__make} install \
	DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%post	-p /sbin/ldconfig
%postun	-p /sbin/ldconfig

%files
%defattr(644,root,root,755)
%doc README
%attr(755,root,root) %{_libdir}/libhpdf-%{version}.so

%files devel
%defattr(644,root,root,755)
%attr(755,root,root) %{_libdir}/libhpdf.so
%{_libdir}/libhpdf.la
%{_includedir}/hpdf*.h

%files static
%defattr(644,root,root,755)
%{_libdir}/libhpdf.a
