{*
 * << Haru Free PDF Library 2.0.3 >> -- hpdf.pas
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 *}

unit hpdf_consts;

interface

uses
  hpdf_types;

const
  HPDF_TRUE = 1;
  HPDF_FALSE = 0;

  HPDF_OK = 0;
  HPDF_NOERROR = 0;

{*----- default values -------------------------------------------------------*}

{* buffer size which is required when we convert to character string. *}
  HPDF_TMP_BUF_SIZ = 256;
  HPDF_SHORT_BUF_SIZ = 32;
  HPDF_REAL_LEN = 11;
  HPDF_INT_LEN = 11;
  HPDF_TEXT_DEFAULT_LEN = 256;
  HPDF_UNICODE_HEADER_LEN = 2;
  HPDF_DATE_TIME_STR_LEN = 23;

{* length of each item defined in PDF *}
  HPDF_BYTE_OFFSET_LEN = 10;
  HPDF_OBJ_ID_LEN = 7;
  HPDF_GEN_NO_LEN = 5;

{* default value of Graphic State *}
  HPDF_DEF_FONT: string = 'Helvetica';
  HPDF_DEF_PAGE_LAYOUT = HPDF_PAGE_LAYOUT_SINGLE;
  HPDF_DEF_PAGE_MODE = HPDF_PAGE_MODE_USE_NONE;
  HPDF_DEF_WORDSPACE= 0;
  HPDF_DEF_CHARSPACE= 0;
  HPDF_DEF_FONTSIZE = 10;
  HPDF_DEF_HSCALING = 100;
  HPDF_DEF_LEADING= 0;
  HPDF_DEF_RENDERING_MODE = HPDF_FILL;
  HPDF_DEF_RAISE= 0;
  HPDF_DEF_LINEWIDTH = 1;
  HPDF_DEF_LINECAP =  HPDF_BUTT_END;
  HPDF_DEF_LINEJOIN = HPDF_MITER_JOIN;
  HPDF_DEF_MITERLIMIT = 10;
  HPDF_DEF_FLATNESS = 1;
  HPDF_DEF_PAGE_NUM = 1;

  HPDF_BS_DEF_WIDTH = 1;

{* defalt page-size *}
  HPDF_DEF_PAGE_WIDTH = 595.276;
  HPDF_DEF_PAGE_HEIGHT = 841.89;

  HPDF_VERSION_TEXT: string = '2.0.3';

{*---------------------------------------------------------------------------*}
{*----- compression mode ----------------------------------------------------*}

  HPDF_COMP_NONE = $00;
  HPDF_COMP_TEXT = $01;
  HPDF_COMP_IMAGE = $02;
  HPDF_COMP_METADATA = $04;
  HPDF_COMP_ALL = $0F;
{*  HPDF_COMP_BEST_COMPRESS = $10;
 *  HPDF_COMP_BEST_SPEED = $20;
 *}
  HPDF_COMP_MASK = $FF;

{*----------------------------------------------------------------------------*}
{*----- permission flags (only Revision 2 is supported)-----------------------*}

  HPDF_ENABLE_READ = 0;
  HPDF_ENABLE_PRINT = 4;
  HPDF_ENABLE_EDIT_ALL = 8;
  HPDF_ENABLE_COPY = 16;
  HPDF_ENABLE_EDIT = 32;


{*----------------------------------------------------------------------------*}
{*------ viewer preferences definitions --------------------------------------*}

  HPDF_HIDE_TOOLBAR = 1;
  HPDF_HIDE_MENUBAR = 2;
  HPDF_HIDE_WINDOW_UI = 4;
  HPDF_FIT_WINDOW = 8;
  HPDF_CENTER_WINDOW = 16;


{*---------------------------------------------------------------------------*}
{*------ limitation of object implementation (PDF1.4) -----------------------*}

  HPDF_LIMIT_MAX_INT = 2147483647;
  HPDF_LIMIT_MIN_INT = -2147483647;

  HPDF_LIMIT_MAX_REAL = 32767;
  HPDF_LIMIT_MIN_REAL = -32767;

  HPDF_LIMIT_MAX_STRING_LEN = 65535;
  HPDF_LIMIT_MAX_NAME_LEN = 127;

  HPDF_LIMIT_MAX_ARRAY = 8191;
  HPDF_LIMIT_MAX_DICT_ELEMENT = 4095;
  HPDF_LIMIT_MAX_XREF_ELEMENT = 8388607;
  HPDF_LIMIT_MAX_GSTATE = 28;
  HPDF_LIMIT_MAX_DEVICE_N = 8;
  HPDF_LIMIT_MAX_DEVICE_N_V15 = 32;
  HPDF_LIMIT_MAX_CID = 65535;
  HPDF_MAX_GENERATION_NUM = 65535;

  HPDF_MIN_PAGE_HEIGHT = 3;
  HPDF_MIN_PAGE_WIDTH = 3;
  HPDF_MAX_PAGE_HEIGHT = 14400;
  HPDF_MAX_PAGE_WIDTH = 14400;
  HPDF_MIN_MAGNIFICATION_FACTOR = 8;
  HPDF_MAX_MAGNIFICATION_FACTOR = 3200;

{*---------------------------------------------------------------------------*}
{*------ limitation of various properties -----------------------------------*}

  HPDF_MIN_PAGE_SIZE = 3;
  HPDF_MAX_PAGE_SIZE = 14400;
  HPDF_MIN_HORIZONTALSCALING = 10;
  HPDF_MAX_HORIZONTALSCALING = 300;
  HPDF_MIN_WORDSPACE = -30;
  HPDF_MAX_WORDSPACE = 300;
  HPDF_MIN_CHARSPACE = -30;
  HPDF_MAX_CHARSPACE = 300;
  HPDF_MAX_FONTSIZE = 300;
  HPDF_MAX_ZOOMSIZE = 10;
  HPDF_MAX_LEADING = 300;
  HPDF_MAX_LINEWIDTH = 100;
  HPDF_MAX_DASH_PATTERN = 100;

{*----------------------------------------------------------------------------*}
{*----- country code definition ----------------------------------------------*}

  HPDF_COUNTRY_AF: string = 'AF';    {* AFGHANISTAN *}
  HPDF_COUNTRY_AL: string = 'AL';    {* ALBANIA *}
  HPDF_COUNTRY_DZ: string = 'DZ';    {* ALGERIA *}
  HPDF_COUNTRY_AS: string = 'AS';    {* AMERICAN SAMOA *}
  HPDF_COUNTRY_AD: string = 'AD';    {* ANDORRA *}
  HPDF_COUNTRY_AO: string = 'AO';    {* ANGOLA *}
  HPDF_COUNTRY_AI: string = 'AI';    {* ANGUILLA *}
  HPDF_COUNTRY_AQ: string = 'AQ';    {* ANTARCTICA *}
  HPDF_COUNTRY_AG: string = 'AG';    {* ANTIGUA AND BARBUDA *}
  HPDF_COUNTRY_AR: string = 'AR';    {* ARGENTINA *}
  HPDF_COUNTRY_AM: string = 'AM';    {* ARMENIA *}
  HPDF_COUNTRY_AW: string = 'AW';    {* ARUBA *}
  HPDF_COUNTRY_AU: string = 'AU';    {* AUSTRALIA *}
  HPDF_COUNTRY_AT: string = 'AT';    {* AUSTRIA *}
  HPDF_COUNTRY_AZ: string = 'AZ';    {* AZERBAIJAN *}
  HPDF_COUNTRY_BS: string = 'BS';    {* BAHAMAS *}
  HPDF_COUNTRY_BH: string = 'BH';    {* BAHRAIN *}
  HPDF_COUNTRY_BD: string = 'BD';    {* BANGLADESH *}
  HPDF_COUNTRY_BB: string = 'BB';    {* BARBADOS *}
  HPDF_COUNTRY_BY: string = 'BY';    {* BELARUS *}
  HPDF_COUNTRY_BE: string = 'BE';    {* BELGIUM *}
  HPDF_COUNTRY_BZ: string = 'BZ';    {* BELIZE *}
  HPDF_COUNTRY_BJ: string = 'BJ';    {* BENIN *}
  HPDF_COUNTRY_BM: string = 'BM';    {* BERMUDA *}
  HPDF_COUNTRY_BT: string = 'BT';    {* BHUTAN *}
  HPDF_COUNTRY_BO: string = 'BO';    {* BOLIVIA *}
  HPDF_COUNTRY_BA: string = 'BA';    {* BOSNIA AND HERZEGOWINA *}
  HPDF_COUNTRY_BW: string = 'BW';    {* BOTSWANA *}
  HPDF_COUNTRY_BV: string = 'BV';    {* BOUVET ISLAND *}
  HPDF_COUNTRY_BR: string = 'BR';    {* BRAZIL *}
  HPDF_COUNTRY_IO: string = 'IO';    {* BRITISH INDIAN OCEAN TERRITORY *}
  HPDF_COUNTRY_BN: string = 'BN';    {* BRUNEI DARUSSALAM *}
  HPDF_COUNTRY_BG: string = 'BG';    {* BULGARIA *}
  HPDF_COUNTRY_BF: string = 'BF';    {* BURKINA FASO *}
  HPDF_COUNTRY_BI: string = 'BI';    {* BURUNDI *}
  HPDF_COUNTRY_KH: string = 'KH';    {* CAMBODIA *}
  HPDF_COUNTRY_CM: string = 'CM';    {* CAMEROON *}
  HPDF_COUNTRY_CA: string = 'CA';    {* CANADA *}
  HPDF_COUNTRY_CV: string = 'CV';    {* CAPE VERDE *}
  HPDF_COUNTRY_KY: string = 'KY';    {* CAYMAN ISLANDS *}
  HPDF_COUNTRY_CF: string = 'CF';    {* CENTRAL AFRICAN REPUBLIC *}
  HPDF_COUNTRY_TD: string = 'TD';    {* CHAD *}
  HPDF_COUNTRY_CL: string = 'CL';    {* CHILE *}
  HPDF_COUNTRY_CN: string = 'CN';    {* CHINA *}
  HPDF_COUNTRY_CX: string = 'CX';    {* CHRISTMAS ISLAND *}
  HPDF_COUNTRY_CC: string = 'CC';    {* COCOS (KEELING) ISLANDS *}
  HPDF_COUNTRY_CO: string = 'CO';    {* COLOMBIA *}
  HPDF_COUNTRY_KM: string = 'KM';    {* COMOROS *}
  HPDF_COUNTRY_CG: string = 'CG';    {* CONGO *}
  HPDF_COUNTRY_CK: string = 'CK';    {* COOK ISLANDS *}
  HPDF_COUNTRY_CR: string = 'CR';    {* COSTA RICA *}
  HPDF_COUNTRY_CI: string = 'CI';    {* COTE D'IVOIRE *}
  HPDF_COUNTRY_HR: string = 'HR';    {* CROATIA (local name: Hrvatska) *}
  HPDF_COUNTRY_CU: string = 'CU';    {* CUBA *}
  HPDF_COUNTRY_CY: string = 'CY';    {* CYPRUS *}
  HPDF_COUNTRY_CZ: string = 'CZ';    {* CZECH REPUBLIC *}
  HPDF_COUNTRY_DK: string = 'DK';    {* DENMARK *}
  HPDF_COUNTRY_DJ: string = 'DJ';    {* DJIBOUTI *}
  HPDF_COUNTRY_DM: string = 'DM';    {* DOMINICA *}
  HPDF_COUNTRY_DO: string = 'DO';    {* DOMINICAN REPUBLIC *}
  HPDF_COUNTRY_TP: string = 'TP';    {* EAST TIMOR *}
  HPDF_COUNTRY_EC: string = 'EC';    {* ECUADOR *}
  HPDF_COUNTRY_EG: string = 'EG';    {* EGYPT *}
  HPDF_COUNTRY_SV: string = 'SV';    {* EL SALVADOR *}
  HPDF_COUNTRY_GQ: string = 'GQ';    {* EQUATORIAL GUINEA *}
  HPDF_COUNTRY_ER: string = 'ER';    {* ERITREA *}
  HPDF_COUNTRY_EE: string = 'EE';    {* ESTONIA *}
  HPDF_COUNTRY_ET: string = 'ET';    {* ETHIOPIA *}
  HPDF_COUNTRY_FK: string = 'FK';    {* FALKLAND ISLANDS (MALVINAS) *}
  HPDF_COUNTRY_FO: string = 'FO';    {* FAROE ISLANDS *}
  HPDF_COUNTRY_FJ: string = 'FJ';    {* FIJI *}
  HPDF_COUNTRY_FI: string = 'FI';    {* FINLAND *}
  HPDF_COUNTRY_FR: string = 'FR';    {* FRANCE *}
  HPDF_COUNTRY_FX: string = 'FX';    {* FRANCE, METROPOLITAN *}
  HPDF_COUNTRY_GF: string = 'GF';    {* FRENCH GUIANA *}
  HPDF_COUNTRY_PF: string = 'PF';    {* FRENCH POLYNESIA *}
  HPDF_COUNTRY_TF: string = 'TF';    {* FRENCH SOUTHERN TERRITORIES *}
  HPDF_COUNTRY_GA: string = 'GA';    {* GABON *}
  HPDF_COUNTRY_GM: string = 'GM';    {* GAMBIA *}
  HPDF_COUNTRY_GE: string = 'GE';    {* GEORGIA *}
  HPDF_COUNTRY_DE: string = 'DE';    {* GERMANY *}
  HPDF_COUNTRY_GH: string = 'GH';    {* GHANA *}
  HPDF_COUNTRY_GI: string = 'GI';    {* GIBRALTAR *}
  HPDF_COUNTRY_GR: string = 'GR';    {* GREECE *}
  HPDF_COUNTRY_GL: string = 'GL';    {* GREENLAND *}
  HPDF_COUNTRY_GD: string = 'GD';    {* GRENADA *}
  HPDF_COUNTRY_GP: string = 'GP';    {* GUADELOUPE *}
  HPDF_COUNTRY_GU: string = 'GU';    {* GUAM *}
  HPDF_COUNTRY_GT: string = 'GT';    {* GUATEMALA *}
  HPDF_COUNTRY_GN: string = 'GN';    {* GUINEA *}
  HPDF_COUNTRY_GW: string = 'GW';    {* GUINEA-BISSAU *}
  HPDF_COUNTRY_GY: string = 'GY';    {* GUYANA *}
  HPDF_COUNTRY_HT: string = 'HT';    {* HAITI *}
  HPDF_COUNTRY_HM: string = 'HM';    {* HEARD AND MC DONALD ISLANDS *}
  HPDF_COUNTRY_HN: string = 'HN';    {* HONDURAS *}
  HPDF_COUNTRY_HK: string = 'HK';    {* HONG KONG *}
  HPDF_COUNTRY_HU: string = 'HU';    {* HUNGARY *}
  HPDF_COUNTRY_IS: string = 'IS';    {* ICELAND *}
  HPDF_COUNTRY_IN: string = 'IN';    {* INDIA *}
  HPDF_COUNTRY_ID: string = 'ID';    {* INDONESIA *}
  HPDF_COUNTRY_IR: string = 'IR';    {* IRAN (ISLAMIC REPUBLIC OF) *}
  HPDF_COUNTRY_IQ: string = 'IQ';    {* IRAQ *}
  HPDF_COUNTRY_IE: string = 'IE';    {* IRELAND *}
  HPDF_COUNTRY_IL: string = 'IL';    {* ISRAEL *}
  HPDF_COUNTRY_IT: string = 'IT';    {* ITALY *}
  HPDF_COUNTRY_JM: string = 'JM';    {* JAMAICA *}
  HPDF_COUNTRY_JP: string = 'JP';    {* JAPAN *}
  HPDF_COUNTRY_JO: string = 'JO';    {* JORDAN *}
  HPDF_COUNTRY_KZ: string = 'KZ';    {* KAZAKHSTAN *}
  HPDF_COUNTRY_KE: string = 'KE';    {* KENYA *}
  HPDF_COUNTRY_KI: string = 'KI';    {* KIRIBATI *}
  HPDF_COUNTRY_KP: string = 'KP';    {* KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF *}
  HPDF_COUNTRY_KR: string = 'KR';    {* KOREA, REPUBLIC OF *}
  HPDF_COUNTRY_KW: string = 'KW';    {* KUWAIT *}
  HPDF_COUNTRY_KG: string = 'KG';    {* KYRGYZSTAN *}
  HPDF_COUNTRY_LA: string = 'LA';    {* LAO PEOPLE'S DEMOCRATIC REPUBLIC *}
  HPDF_COUNTRY_LV: string = 'LV';    {* LATVIA *}
  HPDF_COUNTRY_LB: string = 'LB';    {* LEBANON *}
  HPDF_COUNTRY_LS: string = 'LS';    {* LESOTHO *}
  HPDF_COUNTRY_LR: string = 'LR';    {* LIBERIA *}
  HPDF_COUNTRY_LY: string = 'LY';    {* LIBYAN ARAB JAMAHIRIYA *}
  HPDF_COUNTRY_LI: string = 'LI';    {* LIECHTENSTEIN *}
  HPDF_COUNTRY_LT: string = 'LT';    {* LITHUANIA *}
  HPDF_COUNTRY_LU: string = 'LU';    {* LUXEMBOURG *}
  HPDF_COUNTRY_MO: string = 'MO';    {* MACAU *}
  HPDF_COUNTRY_MK: string = 'MK';    {* MACEDONIA,THE FORMER YUGOSLAV REPUBLIC OF *}
  HPDF_COUNTRY_MG: string = 'MG';    {* MADAGASCAR *}
  HPDF_COUNTRY_MW: string = 'MW';    {* MALAWI *}
  HPDF_COUNTRY_MY: string = 'MY';    {* MALAYSIA *}
  HPDF_COUNTRY_MV: string = 'MV';    {* MALDIVES *}
  HPDF_COUNTRY_ML: string = 'ML';    {* MALI *}
  HPDF_COUNTRY_MT: string = 'MT';    {* MALTA *}
  HPDF_COUNTRY_MH: string = 'MH';    {* MARSHALL ISLANDS *}
  HPDF_COUNTRY_MQ: string = 'MQ';    {* MARTINIQUE *}
  HPDF_COUNTRY_MR: string = 'MR';    {* MAURITANIA *}
  HPDF_COUNTRY_MU: string = 'MU';    {* MAURITIUS *}
  HPDF_COUNTRY_YT: string = 'YT';    {* MAYOTTE *}
  HPDF_COUNTRY_MX: string = 'MX';    {* MEXICO *}
  HPDF_COUNTRY_FM: string = 'FM';    {* MICRONESIA, FEDERATED STATES OF *}
  HPDF_COUNTRY_MD: string = 'MD';    {* MOLDOVA, REPUBLIC OF *}
  HPDF_COUNTRY_MC: string = 'MC';    {* MONACO *}
  HPDF_COUNTRY_MN: string = 'MN';    {* MONGOLIA *}
  HPDF_COUNTRY_MS: string = 'MS';    {* MONTSERRAT *}
  HPDF_COUNTRY_MA: string = 'MA';    {* MOROCCO *}
  HPDF_COUNTRY_MZ: string = 'MZ';    {* MOZAMBIQUE *}
  HPDF_COUNTRY_MM: string = 'MM';    {* MYANMAR *}
  HPDF_COUNTRY_NA: string = 'NA';    {* NAMIBIA *}
  HPDF_COUNTRY_NR: string = 'NR';    {* NAURU *}
  HPDF_COUNTRY_NP: string = 'NP';    {* NEPAL *}
  HPDF_COUNTRY_NL: string = 'NL';    {* NETHERLANDS *}
  HPDF_COUNTRY_AN: string = 'AN';    {* NETHERLANDS ANTILLES *}
  HPDF_COUNTRY_NC: string = 'NC';    {* NEW CALEDONIA *}
  HPDF_COUNTRY_NZ: string = 'NZ';    {* NEW ZEALAND *}
  HPDF_COUNTRY_NI: string = 'NI';    {* NICARAGUA *}
  HPDF_COUNTRY_NE: string = 'NE';    {* NIGER *}
  HPDF_COUNTRY_NG: string = 'NG';    {* NIGERIA *}
  HPDF_COUNTRY_NU: string = 'NU';    {* NIUE *}
  HPDF_COUNTRY_NF: string = 'NF';    {* NORFOLK ISLAND *}
  HPDF_COUNTRY_MP: string = 'MP';    {* NORTHERN MARIANA ISLANDS *}
  HPDF_COUNTRY_NO: string = 'NO';    {* NORWAY *}
  HPDF_COUNTRY_OM: string = 'OM';    {* OMAN *}
  HPDF_COUNTRY_PK: string = 'PK';    {* PAKISTAN *}
  HPDF_COUNTRY_PW: string = 'PW';    {* PALAU *}
  HPDF_COUNTRY_PA: string = 'PA';    {* PANAMA *}
  HPDF_COUNTRY_PG: string = 'PG';    {* PAPUA NEW GUINEA *}
  HPDF_COUNTRY_PY: string = 'PY';    {* PARAGUAY *}
  HPDF_COUNTRY_PE: string = 'PE';    {* PERU *}
  HPDF_COUNTRY_PH: string = 'PH';    {* PHILIPPINES *}
  HPDF_COUNTRY_PN: string = 'PN';    {* PITCAIRN *}
  HPDF_COUNTRY_PL: string = 'PL';    {* POLAND *}
  HPDF_COUNTRY_PT: string = 'PT';    {* PORTUGAL *}
  HPDF_COUNTRY_PR: string = 'PR';    {* PUERTO RICO *}
  HPDF_COUNTRY_QA: string = 'QA';    {* QATAR *}
  HPDF_COUNTRY_RE: string = 'RE';    {* REUNION *}
  HPDF_COUNTRY_RO: string = 'RO';    {* ROMANIA *}
  HPDF_COUNTRY_RU: string = 'RU';    {* RUSSIAN FEDERATION *}
  HPDF_COUNTRY_RW: string = 'RW';    {* RWANDA *}
  HPDF_COUNTRY_KN: string = 'KN';    {* SAINT KITTS AND NEVIS *}
  HPDF_COUNTRY_LC: string = 'LC';    {* SAINT LUCIA *}
  HPDF_COUNTRY_VC: string = 'VC';    {* SAINT VINCENT AND THE GRENADINES *}
  HPDF_COUNTRY_WS: string = 'WS';    {* SAMOA *}
  HPDF_COUNTRY_SM: string = 'SM';    {* SAN MARINO *}
  HPDF_COUNTRY_ST: string = 'ST';    {* SAO TOME AND PRINCIPE *}
  HPDF_COUNTRY_SA: string = 'SA';    {* SAUDI ARABIA *}
  HPDF_COUNTRY_SN: string = 'SN';    {* SENEGAL *}
  HPDF_COUNTRY_SC: string = 'SC';    {* SEYCHELLES *}
  HPDF_COUNTRY_SL: string = 'SL';    {* SIERRA LEONE *}
  HPDF_COUNTRY_SG: string = 'SG';    {* SINGAPORE *}
  HPDF_COUNTRY_SK: string = 'SK';    {* SLOVAKIA (Slovak Republic) *}
  HPDF_COUNTRY_SI: string = 'SI';    {* SLOVENIA *}
  HPDF_COUNTRY_SB: string = 'SB';    {* SOLOMON ISLANDS *}
  HPDF_COUNTRY_SO: string = 'SO';    {* SOMALIA *}
  HPDF_COUNTRY_ZA: string = 'ZA';    {* SOUTH AFRICA *}
  HPDF_COUNTRY_ES: string = 'ES';    {* SPAIN *}
  HPDF_COUNTRY_LK: string = 'LK';    {* SRI LANKA *}
  HPDF_COUNTRY_SH: string = 'SH';    {* ST. HELENA *}
  HPDF_COUNTRY_PM: string = 'PM';    {* ST. PIERRE AND MIQUELON *}
  HPDF_COUNTRY_SD: string = 'SD';    {* SUDAN *}
  HPDF_COUNTRY_SR: string = 'SR';    {* SURINAME *}
  HPDF_COUNTRY_SJ: string = 'SJ';    {* SVALBARD AND JAN MAYEN ISLANDS *}
  HPDF_COUNTRY_SZ: string = 'SZ';    {* SWAZILAND *}
  HPDF_COUNTRY_SE: string = 'SE';    {* SWEDEN *}
  HPDF_COUNTRY_CH: string = 'CH';    {* SWITZERLAND *}
  HPDF_COUNTRY_SY: string = 'SY';    {* SYRIAN ARAB REPUBLIC *}
  HPDF_COUNTRY_TW: string = 'TW';    {* TAIWAN, PROVINCE OF CHINA *}
  HPDF_COUNTRY_TJ: string = 'TJ';    {* TAJIKISTAN *}
  HPDF_COUNTRY_TZ: string = 'TZ';    {* TANZANIA, UNITED REPUBLIC OF *}
  HPDF_COUNTRY_TH: string = 'TH';    {* THAILAND *}
  HPDF_COUNTRY_TG: string = 'TG';    {* TOGO *}
  HPDF_COUNTRY_TK: string = 'TK';    {* TOKELAU *}
  HPDF_COUNTRY_TO: string = 'TO';    {* TONGA *}
  HPDF_COUNTRY_TT: string = 'TT';    {* TRINIDAD AND TOBAGO *}
  HPDF_COUNTRY_TN: string = 'TN';    {* TUNISIA *}
  HPDF_COUNTRY_TR: string = 'TR';    {* TURKEY *}
  HPDF_COUNTRY_TM: string = 'TM';    {* TURKMENISTAN *}
  HPDF_COUNTRY_TC: string = 'TC';    {* TURKS AND CAICOS ISLANDS *}
  HPDF_COUNTRY_TV: string = 'TV';    {* TUVALU *}
  HPDF_COUNTRY_UG: string = 'UG';    {* UGANDA *}
  HPDF_COUNTRY_UA: string = 'UA';    {* UKRAINE *}
  HPDF_COUNTRY_AE: string = 'AE';    {* UNITED ARAB EMIRATES *}
  HPDF_COUNTRY_GB: string = 'GB';    {* UNITED KINGDOM *}
  HPDF_COUNTRY_US: string = 'US';    {* UNITED STATES *}
  HPDF_COUNTRY_UM: string = 'UM';    {* UNITED STATES MINOR OUTLYING ISLANDS *}
  HPDF_COUNTRY_UY: string = 'UY';    {* URUGUAY *}
  HPDF_COUNTRY_UZ: string = 'UZ';    {* UZBEKISTAN *}
  HPDF_COUNTRY_VU: string = 'VU';    {* VANUATU *}
  HPDF_COUNTRY_VA: string = 'VA';    {* VATICAN CITY STATE (HOLY SEE) *}
  HPDF_COUNTRY_VE: string = 'VE';    {* VENEZUELA *}
  HPDF_COUNTRY_VN: string = 'VN';    {* VIET NAM *}
  HPDF_COUNTRY_VG: string = 'VG';    {* VIRGIN ISLANDS (BRITISH) *}
  HPDF_COUNTRY_VI: string = 'VI';    {* VIRGIN ISLANDS (U.S.) *}
  HPDF_COUNTRY_WF: string = 'WF';    {* WALLIS AND FUTUNA ISLANDS *}
  HPDF_COUNTRY_EH: string = 'EH';    {* WESTERN SAHARA *}
  HPDF_COUNTRY_YE: string = 'YE';    {* YEMEN *}
  HPDF_COUNTRY_YU: string = 'YU';    {* YUGOSLAVIA *}
  HPDF_COUNTRY_ZR: string = 'ZR';    {* ZAIRE *}
  HPDF_COUNTRY_ZM: string = 'ZM';    {* ZAMBIA *}
  HPDF_COUNTRY_ZW: string = 'ZW';    {* ZIMBABWE *}

{*----------------------------------------------------------------------------*}
{*----- lang code definition -------------------------------------------------*}

  HPDF_LANG_AA: string = 'aa';    {* Afar *}
  HPDF_LANG_AB: string = 'ab';    {* Abkhazian *}
  HPDF_LANG_AF: string = 'af';    {* Afrikaans *}
  HPDF_LANG_AM: string = 'am';    {* Amharic *}
  HPDF_LANG_AR: string = 'ar';    {* Arabic *}
  HPDF_LANG_AS: string = 'as';    {* Assamese *}
  HPDF_LANG_AY: string = 'ay';    {* Aymara *}
  HPDF_LANG_AZ: string = 'az';    {* Azerbaijani *}
  HPDF_LANG_BA: string = 'ba';    {* Bashkir *}
  HPDF_LANG_BE: string = 'be';    {* Byelorussian *}
  HPDF_LANG_BG: string = 'bg';    {* Bulgarian *}
  HPDF_LANG_BH: string = 'bh';    {* Bihari *}
  HPDF_LANG_BI: string = 'bi';    {* Bislama *}
  HPDF_LANG_BN: string = 'bn';    {* Bengali Bangla *}
  HPDF_LANG_BO: string = 'bo';    {* Tibetan *}
  HPDF_LANG_BR: string = 'br';    {* Breton *}
  HPDF_LANG_CA: string = 'ca';    {* Catalan *}
  HPDF_LANG_CO: string = 'co';    {* Corsican *}
  HPDF_LANG_CS: string = 'cs';    {* Czech *}
  HPDF_LANG_CY: string = 'cy';    {* Welsh *}
  HPDF_LANG_DA: string = 'da';    {* Danish *}
  HPDF_LANG_DE: string = 'de';    {* German *}
  HPDF_LANG_DZ: string = 'dz';    {* Bhutani *}
  HPDF_LANG_EL: string = 'el';    {* Greek *}
  HPDF_LANG_EN: string = 'en';    {* English *}
  HPDF_LANG_EO: string = 'eo';    {* Esperanto *}
  HPDF_LANG_ES: string = 'es';    {* Spanish *}
  HPDF_LANG_ET: string = 'et';    {* Estonian *}
  HPDF_LANG_EU: string = 'eu';    {* Basque *}
  HPDF_LANG_FA: string = 'fa';    {* Persian *}
  HPDF_LANG_FI: string = 'fi';    {* Finnish *}
  HPDF_LANG_FJ: string = 'fj';    {* Fiji *}
  HPDF_LANG_FO: string = 'fo';    {* Faeroese *}
  HPDF_LANG_FR: string = 'fr';    {* French *}
  HPDF_LANG_FY: string = 'fy';    {* Frisian *}
  HPDF_LANG_GA: string = 'ga';    {* Irish *}
  HPDF_LANG_GD: string = 'gd';    {* Scots Gaelic *}
  HPDF_LANG_GL: string = 'gl';    {* Galician *}
  HPDF_LANG_GN: string = 'gn';    {* Guarani *}
  HPDF_LANG_GU: string = 'gu';    {* Gujarati *}
  HPDF_LANG_HA: string = 'ha';    {* Hausa *}
  HPDF_LANG_HI: string = 'hi';    {* Hindi *}
  HPDF_LANG_HR: string = 'hr';    {* Croatian *}
  HPDF_LANG_HU: string = 'hu';    {* Hungarian *}
  HPDF_LANG_HY: string = 'hy';    {* Armenian *}
  HPDF_LANG_IA: string = 'ia';    {* Interlingua *}
  HPDF_LANG_IE: string = 'ie';    {* Interlingue *}
  HPDF_LANG_IK: string = 'ik';    {* Inupiak *}
  HPDF_LANG_IN: string = 'in';    {* Indonesian *}
  HPDF_LANG_IS: string = 'is';    {* Icelandic *}
  HPDF_LANG_IT: string = 'it';    {* Italian *}
  HPDF_LANG_IW: string = 'iw';    {* Hebrew *}
  HPDF_LANG_JA: string = 'ja';    {* Japanese *}
  HPDF_LANG_JI: string = 'ji';    {* Yiddish *}
  HPDF_LANG_JW: string = 'jw';    {* Javanese *}
  HPDF_LANG_KA: string = 'ka';    {* Georgian *}
  HPDF_LANG_KK: string = 'kk';    {* Kazakh *}
  HPDF_LANG_KL: string = 'kl';    {* Greenlandic *}
  HPDF_LANG_KM: string = 'km';    {* Cambodian *}
  HPDF_LANG_KN: string = 'kn';    {* Kannada *}
  HPDF_LANG_KO: string = 'ko';    {* Korean *}
  HPDF_LANG_KS: string = 'ks';    {* Kashmiri *}
  HPDF_LANG_KU: string = 'ku';    {* Kurdish *}
  HPDF_LANG_KY: string = 'ky';    {* Kirghiz *}
  HPDF_LANG_LA: string = 'la';    {* Latin *}
  HPDF_LANG_LN: string = 'ln';    {* Lingala *}
  HPDF_LANG_LO: string = 'lo';    {* Laothian *}
  HPDF_LANG_LT: string = 'lt';    {* Lithuanian *}
  HPDF_LANG_LV: string = 'lv';    {* Latvian,Lettish *}
  HPDF_LANG_MG: string = 'mg';    {* Malagasy *}
  HPDF_LANG_MI: string = 'mi';    {* Maori *}
  HPDF_LANG_MK: string = 'mk';    {* Macedonian *}
  HPDF_LANG_ML: string = 'ml';    {* Malayalam *}
  HPDF_LANG_MN: string = 'mn';    {* Mongolian *}
  HPDF_LANG_MO: string = 'mo';    {* Moldavian *}
  HPDF_LANG_MR: string = 'mr';    {* Marathi *}
  HPDF_LANG_MS: string = 'ms';    {* Malay *}
  HPDF_LANG_MT: string = 'mt';    {* Maltese *}
  HPDF_LANG_MY: string = 'my';    {* Burmese *}
  HPDF_LANG_NA: string = 'na';    {* Nauru *}
  HPDF_LANG_NE: string = 'ne';    {* Nepali *}
  HPDF_LANG_NL: string = 'nl';    {* Dutch *}
  HPDF_LANG_NO: string = 'no';    {* Norwegian *}
  HPDF_LANG_OC: string = 'oc';    {* Occitan *}
  HPDF_LANG_OM: string = 'om';    {* (Afan)Oromo *}
  HPDF_LANG_OR: string = 'or';    {* Oriya *}
  HPDF_LANG_PA: string = 'pa';    {* Punjabi *}
  HPDF_LANG_PL: string = 'pl';    {* Polish *}
  HPDF_LANG_PS: string = 'ps';    {* Pashto,Pushto *}
  HPDF_LANG_PT: string = 'pt';    {* Portuguese  *}
  HPDF_LANG_QU: string = 'qu';    {* Quechua *}
  HPDF_LANG_RM: string = 'rm';    {* Rhaeto-Romance *}
  HPDF_LANG_RN: string = 'rn';    {* Kirundi *}
  HPDF_LANG_RO: string = 'ro';    {* Romanian *}
  HPDF_LANG_RU: string = 'ru';    {* Russian *}
  HPDF_LANG_RW: string = 'rw';    {* Kinyarwanda *}
  HPDF_LANG_SA: string = 'sa';    {* Sanskrit *}
  HPDF_LANG_SD: string = 'sd';    {* Sindhi *}
  HPDF_LANG_SG: string = 'sg';    {* Sangro *}
  HPDF_LANG_SH: string = 'sh';    {* Serbo-Croatian *}
  HPDF_LANG_SI: string = 'si';    {* Singhalese *}
  HPDF_LANG_SK: string = 'sk';    {* Slovak *}
  HPDF_LANG_SL: string = 'sl';    {* Slovenian *}
  HPDF_LANG_SM: string = 'sm';    {* Samoan *}
  HPDF_LANG_SN: string = 'sn';    {* Shona *}
  HPDF_LANG_SO: string = 'so';    {* Somali *}
  HPDF_LANG_SQ: string = 'sq';    {* Albanian *}
  HPDF_LANG_SR: string = 'sr';    {* Serbian *}
  HPDF_LANG_SS: string = 'ss';    {* Siswati *}
  HPDF_LANG_ST: string = 'st';    {* Sesotho *}
  HPDF_LANG_SU: string = 'su';    {* Sundanese *}
  HPDF_LANG_SV: string = 'sv';    {* Swedish *}
  HPDF_LANG_SW: string = 'sw';    {* Swahili *}
  HPDF_LANG_TA: string = 'ta';    {* Tamil *}
  HPDF_LANG_TE: string = 'te';    {* Tegulu *}
  HPDF_LANG_TG: string = 'tg';    {* Tajik *}
  HPDF_LANG_TH: string = 'th';    {* Thai *}
  HPDF_LANG_TI: string = 'ti';    {* Tigrinya *}
  HPDF_LANG_TK: string = 'tk';    {* Turkmen *}
  HPDF_LANG_TL: string = 'tl';    {* Tagalog *}
  HPDF_LANG_TN: string = 'tn';    {* Setswanato Tonga *}
  HPDF_LANG_TR: string = 'tr';    {* Turkish *}
  HPDF_LANG_TS: string = 'ts';    {* Tsonga *}
  HPDF_LANG_TT: string = 'tt';    {* Tatar *}
  HPDF_LANG_TW: string = 'tw';    {* Twi *}
  HPDF_LANG_UK: string = 'uk';    {* Ukrainian *}
  HPDF_LANG_UR: string = 'ur';    {* Urdu *}
  HPDF_LANG_UZ: string = 'uz';    {* Uzbek *}
  HPDF_LANG_VI: string = 'vi';    {* Vietnamese *}
  HPDF_LANG_VO: string = 'vo';    {* Volapuk *}
  HPDF_LANG_WO: string = 'wo';    {* Wolof *}
  HPDF_LANG_XH: string = 'xh';    {* Xhosa *}
  HPDF_LANG_YO: string = 'yo';    {* Yoruba *}
  HPDF_LANG_ZH: string = 'zh';    {* Chinese *}
  HPDF_LANG_ZU: string = 'zu';    {* Zulu *}


{*----------------------------------------------------------------------------*}
{*----- Graphis mode ---------------------------------------------------------*}

  HPDF_GMODE_PAGE_DESCRIPTION = $0001;
  HPDF_GMODE_PATH_OBJECT = $0002;
  HPDF_GMODE_TEXT_OBJECT = $0004;
  HPDF_GMODE_CLIPPING_PATH = $0008;
  HPDF_GMODE_SHADING = $0010;
  HPDF_GMODE_INLINE_IMAGE =  $0020;
  HPDF_GMODE_EXTERNAL_OBJECT = $0040;

{*----------------------------------------------------------------------------*}

implementation

end.

