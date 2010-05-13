###
## * << Haru Free PDF Library 2.0.8 >> -- hpdf_consts.h
## *
## * URL http://libharu.org/
## *
## * Copyright (c) 1999-2006 Takeshi Kanno
## *
## * Permission to use, copy, modify, distribute and sell this software
## * and its documentation for any purpose is hereby granted without fee,
## * provided that the above copyright notice appear in all copies and
## * that both that copyright notice and this permission notice appear
## * in supporting documentation.
## * It is provided "as is" without express or implied warranty.
## *
##

## port to python by Li Jun
## http://groups.google.com/group/pythoncia

from hpdf_types import *

#----------------------------------------------------------------------------

HPDF_TRUE                  =1
HPDF_FALSE                 =0

HPDF_OK                    =0
HPDF_NOERROR               =0

#----- default values -------------------------------------------------------

# buffer size which is required when we convert to character string.
HPDF_TMP_BUF_SIZ           =512
HPDF_SHORT_BUF_SIZ         =32
HPDF_REAL_LEN              =11
HPDF_INT_LEN               =11
HPDF_TEXT_DEFAULT_LEN      =256
HPDF_UNICODE_HEADER_LEN    =2
HPDF_DATE_TIME_STR_LEN     =23

# length of each item defined in PDF
HPDF_BYTE_OFFSET_LEN       =10
HPDF_OBJ_ID_LEN            =7
HPDF_GEN_NO_LEN            =5

# default value of Graphic State
HPDF_DEF_FONT              ="Helvetica"
HPDF_DEF_PAGE_LAYOUT       =HPDF_PAGE_LAYOUT_SINGLE
HPDF_DEF_PAGE_MODE         =HPDF_PAGE_MODE_USE_NONE
HPDF_DEF_WORDSPACE         =0
HPDF_DEF_CHARSPACE         =0
HPDF_DEF_FONTSIZE          =10
HPDF_DEF_HSCALING          =100
HPDF_DEF_LEADING           =0
HPDF_DEF_RENDERING_MODE    =HPDF_FILL
HPDF_DEF_RISE              =0
HPDF_DEF_RAISE             =HPDF_DEF_RISE
HPDF_DEF_LINEWIDTH         =1
HPDF_DEF_LINECAP           =HPDF_BUTT_END
HPDF_DEF_LINEJOIN          =HPDF_MITER_JOIN
HPDF_DEF_MITERLIMIT        =10
HPDF_DEF_FLATNESS          =1
HPDF_DEF_PAGE_NUM          =1

HPDF_BS_DEF_WIDTH          =1

# defalt page-size
HPDF_DEF_PAGE_WIDTH        =595.276
HPDF_DEF_PAGE_HEIGHT       =841.89

HPDF_VERSION_TEXT          ="2.0.8"

#---------------------------------------------------------------------------
#----- compression mode ----------------------------------------------------

HPDF_COMP_NONE           =0x00
HPDF_COMP_TEXT           =0x01
HPDF_COMP_IMAGE          =0x02
HPDF_COMP_METADATA       =0x04
HPDF_COMP_ALL            =0x0F
HPDF_COMP_BEST_COMPRESS  =0x10
HPDF_COMP_BEST_SPEED     =0x20

HPDF_COMP_MASK           =0xFF


#----------------------------------------------------------------------------
#----- permission flags (only Revision 2 is supported)-----------------------

HPDF_ENABLE_READ        =0
HPDF_ENABLE_PRINT       =4
HPDF_ENABLE_EDIT_ALL    =8
HPDF_ENABLE_COPY        =16
HPDF_ENABLE_EDIT        =32


#----------------------------------------------------------------------------
#------ viewer preferences definitions --------------------------------------

HPDF_HIDE_TOOLBAR   =1
HPDF_HIDE_MENUBAR   =2
HPDF_HIDE_WINDOW_UI =4
HPDF_FIT_WINDOW     =8
HPDF_CENTER_WINDOW  =16


#---------------------------------------------------------------------------
#------ limitation of object implementation (PDF1.4) -----------------------

HPDF_LIMIT_MAX_INT            =2147483647
HPDF_LIMIT_MIN_INT            =-2147483647

HPDF_LIMIT_MAX_REAL           =32767
HPDF_LIMIT_MIN_REAL           =-32767

HPDF_LIMIT_MAX_STRING_LEN     =65535
HPDF_LIMIT_MAX_NAME_LEN       =127

HPDF_LIMIT_MAX_ARRAY          =8191
HPDF_LIMIT_MAX_DICT_ELEMENT   =4095
HPDF_LIMIT_MAX_XREF_ELEMENT   =8388607
HPDF_LIMIT_MAX_GSTATE         =28
HPDF_LIMIT_MAX_DEVICE_N       =8
HPDF_LIMIT_MAX_DEVICE_N_V15   =32
HPDF_LIMIT_MAX_CID            =65535
HPDF_MAX_GENERATION_NUM       =65535

HPDF_MIN_PAGE_HEIGHT          =3
HPDF_MIN_PAGE_WIDTH           =3
HPDF_MAX_PAGE_HEIGHT          =14400
HPDF_MAX_PAGE_WIDTH           =14400
HPDF_MIN_MAGNIFICATION_FACTOR =8
HPDF_MAX_MAGNIFICATION_FACTOR =3200

#---------------------------------------------------------------------------
#------ limitation of various properties -----------------------------------

HPDF_MIN_PAGE_SIZE         =3
HPDF_MAX_PAGE_SIZE         =14400
HPDF_MIN_HORIZONTALSCALING =10
HPDF_MAX_HORIZONTALSCALING =300
HPDF_MIN_WORDSPACE         =-30
HPDF_MAX_WORDSPACE         =300
HPDF_MIN_CHARSPACE         =-30
HPDF_MAX_CHARSPACE         =300
HPDF_MAX_FONTSIZE          =300
HPDF_MAX_ZOOMSIZE          =10
HPDF_MAX_LEADING           =300
HPDF_MAX_LINEWIDTH         =100
HPDF_MAX_DASH_PATTERN      =100

HPDF_MAX_JWW_NUM           =128

#----------------------------------------------------------------------------
#----- country code definition ----------------------------------------------

HPDF_COUNTRY_AF ="AF"    # AFGHANISTAN
HPDF_COUNTRY_AL ="AL"    # ALBANIA
HPDF_COUNTRY_DZ ="DZ"    # ALGERIA
HPDF_COUNTRY_AS ="AS"    # AMERICAN SAMOA
HPDF_COUNTRY_AD ="AD"    # ANDORRA
HPDF_COUNTRY_AO ="AO"    # ANGOLA
HPDF_COUNTRY_AI ="AI"    # ANGUILLA
HPDF_COUNTRY_AQ ="AQ"    # ANTARCTICA
HPDF_COUNTRY_AG ="AG"    # ANTIGUA AND BARBUDA
HPDF_COUNTRY_AR ="AR"    # ARGENTINA
HPDF_COUNTRY_AM ="AM"    # ARMENIA
HPDF_COUNTRY_AW ="AW"    # ARUBA
HPDF_COUNTRY_AU ="AU"    # AUSTRALIA
HPDF_COUNTRY_AT ="AT"    # AUSTRIA
HPDF_COUNTRY_AZ ="AZ"    # AZERBAIJAN
HPDF_COUNTRY_BS ="BS"    # BAHAMAS
HPDF_COUNTRY_BH ="BH"    # BAHRAIN
HPDF_COUNTRY_BD ="BD"    # BANGLADESH
HPDF_COUNTRY_BB ="BB"    # BARBADOS
HPDF_COUNTRY_BY ="BY"    # BELARUS
HPDF_COUNTRY_BE ="BE"    # BELGIUM
HPDF_COUNTRY_BZ ="BZ"    # BELIZE
HPDF_COUNTRY_BJ ="BJ"    # BENIN
HPDF_COUNTRY_BM ="BM"    # BERMUDA
HPDF_COUNTRY_BT ="BT"    # BHUTAN
HPDF_COUNTRY_BO ="BO"    # BOLIVIA
HPDF_COUNTRY_BA ="BA"    # BOSNIA AND HERZEGOWINA
HPDF_COUNTRY_BW ="BW"    # BOTSWANA
HPDF_COUNTRY_BV ="BV"    # BOUVET ISLAND
HPDF_COUNTRY_BR ="BR"    # BRAZIL
HPDF_COUNTRY_IO ="IO"    # BRITISH INDIAN OCEAN TERRITORY
HPDF_COUNTRY_BN ="BN"    # BRUNEI DARUSSALAM
HPDF_COUNTRY_BG ="BG"    # BULGARIA
HPDF_COUNTRY_BF ="BF"    # BURKINA FASO
HPDF_COUNTRY_BI ="BI"    # BURUNDI
HPDF_COUNTRY_KH ="KH"    # CAMBODIA
HPDF_COUNTRY_CM ="CM"    # CAMEROON
HPDF_COUNTRY_CA ="CA"    # CANADA
HPDF_COUNTRY_CV ="CV"    # CAPE VERDE
HPDF_COUNTRY_KY ="KY"    # CAYMAN ISLANDS
HPDF_COUNTRY_CF ="CF"    # CENTRAL AFRICAN REPUBLIC
HPDF_COUNTRY_TD ="TD"    # CHAD
HPDF_COUNTRY_CL ="CL"    # CHILE
HPDF_COUNTRY_CN ="CN"    # CHINA
HPDF_COUNTRY_CX ="CX"    # CHRISTMAS ISLAND
HPDF_COUNTRY_CC ="CC"    # COCOS (KEELING) ISLANDS
HPDF_COUNTRY_CO ="CO"    # COLOMBIA
HPDF_COUNTRY_KM ="KM"    # COMOROS
HPDF_COUNTRY_CG ="CG"    # CONGO
HPDF_COUNTRY_CK ="CK"    # COOK ISLANDS
HPDF_COUNTRY_CR ="CR"    # COSTA RICA
HPDF_COUNTRY_CI ="CI"    # COTE D'IVOIRE
HPDF_COUNTRY_HR ="HR"    # CROATIA (local name: Hrvatska)
HPDF_COUNTRY_CU ="CU"    # CUBA
HPDF_COUNTRY_CY ="CY"    # CYPRUS
HPDF_COUNTRY_CZ ="CZ"    # CZECH REPUBLIC
HPDF_COUNTRY_DK ="DK"    # DENMARK
HPDF_COUNTRY_DJ ="DJ"    # DJIBOUTI
HPDF_COUNTRY_DM ="DM"    # DOMINICA
HPDF_COUNTRY_DO ="DO"    # DOMINICAN REPUBLIC
HPDF_COUNTRY_TP ="TP"    # EAST TIMOR
HPDF_COUNTRY_EC ="EC"    # ECUADOR
HPDF_COUNTRY_EG ="EG"    # EGYPT
HPDF_COUNTRY_SV ="SV"    # EL SALVADOR
HPDF_COUNTRY_GQ ="GQ"    # EQUATORIAL GUINEA
HPDF_COUNTRY_ER ="ER"    # ERITREA
HPDF_COUNTRY_EE ="EE"    # ESTONIA
HPDF_COUNTRY_ET ="ET"    # ETHIOPIA
HPDF_COUNTRY_FK ="FK"   # FALKLAND ISLANDS (MALVINAS)
HPDF_COUNTRY_FO ="FO"    # FAROE ISLANDS
HPDF_COUNTRY_FJ ="FJ"    # FIJI
HPDF_COUNTRY_FI ="FI"    # FINLAND
HPDF_COUNTRY_FR ="FR"    # FRANCE
HPDF_COUNTRY_FX ="FX"    # FRANCE, METROPOLITAN
HPDF_COUNTRY_GF ="GF"    # FRENCH GUIANA
HPDF_COUNTRY_PF ="PF"    # FRENCH POLYNESIA
HPDF_COUNTRY_TF ="TF"    # FRENCH SOUTHERN TERRITORIES
HPDF_COUNTRY_GA ="GA"    # GABON
HPDF_COUNTRY_GM ="GM"    # GAMBIA
HPDF_COUNTRY_GE ="GE"    # GEORGIA
HPDF_COUNTRY_DE ="DE"    # GERMANY
HPDF_COUNTRY_GH ="GH"    # GHANA
HPDF_COUNTRY_GI ="GI"    # GIBRALTAR
HPDF_COUNTRY_GR ="GR"    # GREECE
HPDF_COUNTRY_GL ="GL"    # GREENLAND
HPDF_COUNTRY_GD ="GD"    # GRENADA
HPDF_COUNTRY_GP ="GP"    # GUADELOUPE
HPDF_COUNTRY_GU ="GU"    # GUAM
HPDF_COUNTRY_GT ="GT"    # GUATEMALA
HPDF_COUNTRY_GN ="GN"    # GUINEA
HPDF_COUNTRY_GW ="GW"    # GUINEA-BISSAU
HPDF_COUNTRY_GY ="GY"    # GUYANA
HPDF_COUNTRY_HT ="HT"    # HAITI
HPDF_COUNTRY_HM ="HM"    # HEARD AND MC DONALD ISLANDS
HPDF_COUNTRY_HN ="HN"    # HONDURAS
HPDF_COUNTRY_HK ="HK"    # HONG KONG
HPDF_COUNTRY_HU ="HU"    # HUNGARY
HPDF_COUNTRY_IS ="IS"    # ICELAND
HPDF_COUNTRY_IN ="IN"    # INDIA
HPDF_COUNTRY_ID ="ID"    # INDONESIA
HPDF_COUNTRY_IR ="IR"    # IRAN (ISLAMIC REPUBLIC OF)
HPDF_COUNTRY_IQ ="IQ"    # IRAQ
HPDF_COUNTRY_IE ="IE"    # IRELAND
HPDF_COUNTRY_IL ="IL"    # ISRAEL
HPDF_COUNTRY_IT ="IT"    # ITALY
HPDF_COUNTRY_JM ="JM"    # JAMAICA
HPDF_COUNTRY_JP ="JP"    # JAPAN
HPDF_COUNTRY_JO ="JO"    # JORDAN
HPDF_COUNTRY_KZ ="KZ"    # KAZAKHSTAN
HPDF_COUNTRY_KE ="KE"    # KENYA
HPDF_COUNTRY_KI ="KI"    # KIRIBATI
HPDF_COUNTRY_KP ="KP"    # KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF
HPDF_COUNTRY_KR ="KR"    # KOREA, REPUBLIC OF
HPDF_COUNTRY_KW ="KW"    # KUWAIT
HPDF_COUNTRY_KG ="KG"    # KYRGYZSTAN
HPDF_COUNTRY_LA ="LA"    # LAO PEOPLE'S DEMOCRATIC REPUBLIC
HPDF_COUNTRY_LV ="LV"    # LATVIA
HPDF_COUNTRY_LB ="LB"    # LEBANON
HPDF_COUNTRY_LS ="LS"    # LESOTHO
HPDF_COUNTRY_LR ="LR"    # LIBERIA
HPDF_COUNTRY_LY ="LY"    # LIBYAN ARAB JAMAHIRIYA
HPDF_COUNTRY_LI ="LI"    # LIECHTENSTEIN
HPDF_COUNTRY_LT ="LT"    # LITHUANIA
HPDF_COUNTRY_LU ="LU"    # LUXEMBOURG
HPDF_COUNTRY_MO ="MO"    # MACAU
HPDF_COUNTRY_MK ="MK"    # MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF
HPDF_COUNTRY_MG ="MG"    # MADAGASCAR
HPDF_COUNTRY_MW ="MW"    # MALAWI
HPDF_COUNTRY_MY ="MY"    # MALAYSIA
HPDF_COUNTRY_MV ="MV"    # MALDIVES
HPDF_COUNTRY_ML ="ML"    # MALI
HPDF_COUNTRY_MT ="MT"    # MALTA
HPDF_COUNTRY_MH ="MH"    # MARSHALL ISLANDS
HPDF_COUNTRY_MQ ="MQ"    # MARTINIQUE
HPDF_COUNTRY_MR ="MR"    # MAURITANIA
HPDF_COUNTRY_MU ="MU"    # MAURITIUS
HPDF_COUNTRY_YT ="YT"    # MAYOTTE
HPDF_COUNTRY_MX ="MX"    # MEXICO
HPDF_COUNTRY_FM ="FM"    # MICRONESIA, FEDERATED STATES OF
HPDF_COUNTRY_MD ="MD"    # MOLDOVA, REPUBLIC OF
HPDF_COUNTRY_MC ="MC"    # MONACO
HPDF_COUNTRY_MN ="MN"    # MONGOLIA
HPDF_COUNTRY_MS ="MS"    # MONTSERRAT
HPDF_COUNTRY_MA ="MA"    # MOROCCO
HPDF_COUNTRY_MZ ="MZ"    # MOZAMBIQUE
HPDF_COUNTRY_MM ="MM"    # MYANMAR
HPDF_COUNTRY_NA ="NA"    # NAMIBIA
HPDF_COUNTRY_NR ="NR"    # NAURU
HPDF_COUNTRY_NP ="NP"    # NEPAL
HPDF_COUNTRY_NL ="NL"    # NETHERLANDS
HPDF_COUNTRY_AN ="AN"    # NETHERLANDS ANTILLES
HPDF_COUNTRY_NC ="NC"    # NEW CALEDONIA
HPDF_COUNTRY_NZ ="NZ"    # NEW ZEALAND
HPDF_COUNTRY_NI ="NI"    # NICARAGUA
HPDF_COUNTRY_NE ="NE"    # NIGER
HPDF_COUNTRY_NG ="NG"    # NIGERIA
HPDF_COUNTRY_NU ="NU"    # NIUE
HPDF_COUNTRY_NF ="NF"    # NORFOLK ISLAND
HPDF_COUNTRY_MP ="MP"    # NORTHERN MARIANA ISLANDS
HPDF_COUNTRY_NO ="NO"    # NORWAY
HPDF_COUNTRY_OM ="OM"    # OMAN
HPDF_COUNTRY_PK ="PK"    # PAKISTAN
HPDF_COUNTRY_PW ="PW"    # PALAU
HPDF_COUNTRY_PA ="PA"    # PANAMA
HPDF_COUNTRY_PG ="PG"    # PAPUA NEW GUINEA
HPDF_COUNTRY_PY ="PY"    # PARAGUAY
HPDF_COUNTRY_PE ="PE"    # PERU
HPDF_COUNTRY_PH ="PH"    # PHILIPPINES
HPDF_COUNTRY_PN ="PN"    # PITCAIRN
HPDF_COUNTRY_PL ="PL"    # POLAND
HPDF_COUNTRY_PT ="PT"    # PORTUGAL
HPDF_COUNTRY_PR ="PR"    # PUERTO RICO
HPDF_COUNTRY_QA ="QA"    # QATAR
HPDF_COUNTRY_RE ="RE"    # REUNION
HPDF_COUNTRY_RO ="RO"    # ROMANIA
HPDF_COUNTRY_RU ="RU"    # RUSSIAN FEDERATION
HPDF_COUNTRY_RW ="RW"    # RWANDA
HPDF_COUNTRY_KN ="KN"    # SAINT KITTS AND NEVIS
HPDF_COUNTRY_LC ="LC"    # SAINT LUCIA
HPDF_COUNTRY_VC ="VC"    # SAINT VINCENT AND THE GRENADINES
HPDF_COUNTRY_WS ="WS"    # SAMOA
HPDF_COUNTRY_SM ="SM"    # SAN MARINO
HPDF_COUNTRY_ST ="ST"    # SAO TOME AND PRINCIPE
HPDF_COUNTRY_SA ="SA"    # SAUDI ARABIA
HPDF_COUNTRY_SN ="SN"    # SENEGAL
HPDF_COUNTRY_SC ="SC"    # SEYCHELLES
HPDF_COUNTRY_SL ="SL"    # SIERRA LEONE
HPDF_COUNTRY_SG ="SG"    # SINGAPORE
HPDF_COUNTRY_SK ="SK"    # SLOVAKIA (Slovak Republic)
HPDF_COUNTRY_SI ="SI"    # SLOVENIA
HPDF_COUNTRY_SB ="SB"    # SOLOMON ISLANDS
HPDF_COUNTRY_SO ="SO"    # SOMALIA
HPDF_COUNTRY_ZA ="ZA"    # SOUTH AFRICA
HPDF_COUNTRY_ES ="ES"    # SPAIN
HPDF_COUNTRY_LK ="LK"    # SRI LANKA
HPDF_COUNTRY_SH ="SH"    # ST. HELENA
HPDF_COUNTRY_PM ="PM"    # ST. PIERRE AND MIQUELON
HPDF_COUNTRY_SD ="SD"    # SUDAN
HPDF_COUNTRY_SR ="SR"    # SURINAME
HPDF_COUNTRY_SJ ="SJ"    # SVALBARD AND JAN MAYEN ISLANDS
HPDF_COUNTRY_SZ ="SZ"    # SWAZILAND
HPDF_COUNTRY_SE ="SE"    # SWEDEN
HPDF_COUNTRY_CH ="CH"    # SWITZERLAND
HPDF_COUNTRY_SY ="SY"    # SYRIAN ARAB REPUBLIC
HPDF_COUNTRY_TW ="TW"    # TAIWAN, PROVINCE OF CHINA
HPDF_COUNTRY_TJ ="TJ"    # TAJIKISTAN
HPDF_COUNTRY_TZ ="TZ"    # TANZANIA, UNITED REPUBLIC OF
HPDF_COUNTRY_TH ="TH"    # THAILAND
HPDF_COUNTRY_TG ="TG"    # TOGO
HPDF_COUNTRY_TK ="TK"    # TOKELAU
HPDF_COUNTRY_TO ="TO"    # TONGA
HPDF_COUNTRY_TT ="TT"    # TRINIDAD AND TOBAGO
HPDF_COUNTRY_TN ="TN"    # TUNISIA
HPDF_COUNTRY_TR ="TR"    # TURKEY
HPDF_COUNTRY_TM ="TM"    # TURKMENISTAN
HPDF_COUNTRY_TC ="TC"    # TURKS AND CAICOS ISLANDS
HPDF_COUNTRY_TV ="TV"    # TUVALU
HPDF_COUNTRY_UG ="UG"    # UGANDA
HPDF_COUNTRY_UA ="UA"    # UKRAINE
HPDF_COUNTRY_AE ="AE"    # UNITED ARAB EMIRATES
HPDF_COUNTRY_GB ="GB"    # UNITED KINGDOM
HPDF_COUNTRY_US ="US"    # UNITED STATES
HPDF_COUNTRY_UM ="UM"    # UNITED STATES MINOR OUTLYING ISLANDS
HPDF_COUNTRY_UY ="UY"    # URUGUAY
HPDF_COUNTRY_UZ ="UZ"    # UZBEKISTAN
HPDF_COUNTRY_VU ="VU"    # VANUATU
HPDF_COUNTRY_VA ="VA"    # VATICAN CITY STATE (HOLY SEE)
HPDF_COUNTRY_VE ="VE"    # VENEZUELA
HPDF_COUNTRY_VN ="VN"    # VIET NAM
HPDF_COUNTRY_VG ="VG"    # VIRGIN ISLANDS (BRITISH)
HPDF_COUNTRY_VI ="VI"    # VIRGIN ISLANDS (U.S.)
HPDF_COUNTRY_WF ="WF"    # WALLIS AND FUTUNA ISLANDS
HPDF_COUNTRY_EH ="EH"    # WESTERN SAHARA
HPDF_COUNTRY_YE ="YE"    # YEMEN
HPDF_COUNTRY_YU ="YU"    # YUGOSLAVIA
HPDF_COUNTRY_ZR ="ZR"    # ZAIRE
HPDF_COUNTRY_ZM ="ZM"    # ZAMBIA
HPDF_COUNTRY_ZW ="ZW"    # ZIMBABWE

#----------------------------------------------------------------------------
#----- lang code definition -------------------------------------------------

HPDF_LANG_AA   ="aa"     # Afar
HPDF_LANG_AB   ="ab"     # Abkhazian
HPDF_LANG_AF   ="af"     # Afrikaans
HPDF_LANG_AM   ="am"     # Amharic
HPDF_LANG_AR   ="ar"     # Arabic
HPDF_LANG_AS   ="as"     # Assamese
HPDF_LANG_AY   ="ay"     # Aymara
HPDF_LANG_AZ   ="az"     # Azerbaijani
HPDF_LANG_BA   ="ba"     # Bashkir
HPDF_LANG_BE   ="be"     # Byelorussian
HPDF_LANG_BG   ="bg"     # Bulgarian
HPDF_LANG_BH   ="bh"     # Bihari
HPDF_LANG_BI   ="bi"     # Bislama
HPDF_LANG_BN   ="bn"     # Bengali Bangla
HPDF_LANG_BO   ="bo"     # Tibetan
HPDF_LANG_BR   ="br"     # Breton
HPDF_LANG_CA   ="ca"     # Catalan
HPDF_LANG_CO   ="co"     # Corsican
HPDF_LANG_CS   ="cs"     # Czech
HPDF_LANG_CY   ="cy"     # Welsh
HPDF_LANG_DA   ="da"     # Danish
HPDF_LANG_DE   ="de"     # German
HPDF_LANG_DZ   ="dz"     # Bhutani
HPDF_LANG_EL   ="el"     # Greek
HPDF_LANG_EN   ="en"     # English
HPDF_LANG_EO   ="eo"     # Esperanto
HPDF_LANG_ES   ="es"     # Spanish
HPDF_LANG_ET   ="et"     # Estonian
HPDF_LANG_EU   ="eu"     # Basque
HPDF_LANG_FA   ="fa"     # Persian
HPDF_LANG_FI   ="fi"     # Finnish
HPDF_LANG_FJ   ="fj"     # Fiji
HPDF_LANG_FO   ="fo"     # Faeroese
HPDF_LANG_FR   ="fr"     # French
HPDF_LANG_FY   ="fy"     # Frisian
HPDF_LANG_GA   ="ga"     # Irish
HPDF_LANG_GD   ="gd"     # Scots Gaelic
HPDF_LANG_GL   ="gl"     # Galician
HPDF_LANG_GN   ="gn"     # Guarani
HPDF_LANG_GU   ="gu"     # Gujarati
HPDF_LANG_HA   ="ha"     # Hausa
HPDF_LANG_HI   ="hi"     # Hindi
HPDF_LANG_HR   ="hr"     # Croatian
HPDF_LANG_HU   ="hu"     # Hungarian
HPDF_LANG_HY   ="hy"     # Armenian
HPDF_LANG_IA   ="ia"     # Interlingua
HPDF_LANG_IE   ="ie"     # Interlingue
HPDF_LANG_IK   ="ik"     # Inupiak
HPDF_LANG_IN   ="in"     # Indonesian
HPDF_LANG_IS   ="is"     # Icelandic
HPDF_LANG_IT   ="it"     # Italian
HPDF_LANG_IW   ="iw"     # Hebrew
HPDF_LANG_JA   ="ja"     # Japanese
HPDF_LANG_JI   ="ji"     # Yiddish
HPDF_LANG_JW   ="jw"     # Javanese
HPDF_LANG_KA   ="ka"     # Georgian
HPDF_LANG_KK   ="kk"     # Kazakh
HPDF_LANG_KL   ="kl"     # Greenlandic
HPDF_LANG_KM   ="km"     # Cambodian
HPDF_LANG_KN   ="kn"     # Kannada
HPDF_LANG_KO   ="ko"     # Korean
HPDF_LANG_KS   ="ks"     # Kashmiri
HPDF_LANG_KU   ="ku"     # Kurdish
HPDF_LANG_KY   ="ky"     # Kirghiz
HPDF_LANG_LA   ="la"     # Latin
HPDF_LANG_LN   ="ln"     # Lingala
HPDF_LANG_LO   ="lo"     # Laothian
HPDF_LANG_LT   ="lt"     # Lithuanian
HPDF_LANG_LV   ="lv"     # Latvian,Lettish
HPDF_LANG_MG   ="mg"     # Malagasy
HPDF_LANG_MI   ="mi"     # Maori
HPDF_LANG_MK   ="mk"     # Macedonian
HPDF_LANG_ML   ="ml"     # Malayalam
HPDF_LANG_MN   ="mn"     # Mongolian
HPDF_LANG_MO   ="mo"     # Moldavian
HPDF_LANG_MR   ="mr"     # Marathi
HPDF_LANG_MS   ="ms"     # Malay
HPDF_LANG_MT   ="mt"     # Maltese
HPDF_LANG_MY   ="my"     # Burmese
HPDF_LANG_NA   ="na"     # Nauru
HPDF_LANG_NE   ="ne"     # Nepali
HPDF_LANG_NL   ="nl"     # Dutch
HPDF_LANG_NO   ="no"     # Norwegian
HPDF_LANG_OC   ="oc"     # Occitan
HPDF_LANG_OM   ="om"     # (Afan)Oromo
HPDF_LANG_OR   ="or"     # Oriya
HPDF_LANG_PA   ="pa"     # Punjabi
HPDF_LANG_PL   ="pl"     # Polish
HPDF_LANG_PS   ="ps"     # Pashto,Pushto
HPDF_LANG_PT   ="pt"     # Portuguese
HPDF_LANG_QU   ="qu"     # Quechua
HPDF_LANG_RM   ="rm"     # Rhaeto-Romance
HPDF_LANG_RN   ="rn"     # Kirundi
HPDF_LANG_RO   ="ro"     # Romanian
HPDF_LANG_RU   ="ru"     # Russian
HPDF_LANG_RW   ="rw"     # Kinyarwanda
HPDF_LANG_SA   ="sa"     # Sanskrit
HPDF_LANG_SD   ="sd"     # Sindhi
HPDF_LANG_SG   ="sg"     # Sangro
HPDF_LANG_SH   ="sh"     # Serbo-Croatian
HPDF_LANG_SI   ="si"     # Singhalese
HPDF_LANG_SK   ="sk"     # Slovak
HPDF_LANG_SL   ="sl"     # Slovenian
HPDF_LANG_SM   ="sm"     # Samoan
HPDF_LANG_SN   ="sn"     # Shona
HPDF_LANG_SO   ="so"     # Somali
HPDF_LANG_SQ   ="sq"     # Albanian
HPDF_LANG_SR   ="sr"     # Serbian
HPDF_LANG_SS   ="ss"     # Siswati
HPDF_LANG_ST   ="st"     # Sesotho
HPDF_LANG_SU   ="su"     # Sundanese
HPDF_LANG_SV   ="sv"     # Swedish
HPDF_LANG_SW   ="sw"     # Swahili
HPDF_LANG_TA   ="ta"     # Tamil
HPDF_LANG_TE   ="te"     # Tegulu
HPDF_LANG_TG   ="tg"     # Tajik
HPDF_LANG_TH   ="th"     # Thai
HPDF_LANG_TI   ="ti"     # Tigrinya
HPDF_LANG_TK   ="tk"     # Turkmen
HPDF_LANG_TL   ="tl"     # Tagalog
HPDF_LANG_TN   ="tn"     # Setswanato Tonga
HPDF_LANG_TR   ="tr"     # Turkish
HPDF_LANG_TS   ="ts"     # Tsonga
HPDF_LANG_TT   ="tt"     # Tatar
HPDF_LANG_TW   ="tw"     # Twi
HPDF_LANG_UK   ="uk"     # Ukrainian
HPDF_LANG_UR   ="ur"     # Urdu
HPDF_LANG_UZ   ="uz"     # Uzbek
HPDF_LANG_VI   ="vi"     # Vietnamese
HPDF_LANG_VO   ="vo"     # Volapuk
HPDF_LANG_WO   ="wo"     # Wolof
HPDF_LANG_XH   ="xh"     # Xhosa
HPDF_LANG_YO   ="yo"     # Yoruba
HPDF_LANG_ZH   ="zh"     # Chinese
HPDF_LANG_ZU   ="zu"     # Zulu


#----------------------------------------------------------------------------
#----- Graphis mode ---------------------------------------------------------

HPDF_GMODE_PAGE_DESCRIPTION      =0x0001
HPDF_GMODE_PATH_OBJECT           =0x0002
HPDF_GMODE_TEXT_OBJECT           =0x0004
HPDF_GMODE_CLIPPING_PATH         =0x0008
HPDF_GMODE_SHADING               =0x0010
HPDF_GMODE_INLINE_IMAGE          =0x0020
HPDF_GMODE_EXTERNAL_OBJECT       =0x0040
