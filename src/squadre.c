/*
*Autori : Alessandro Pezzè 158629, Norbert Paissan 157610
*Progetto : 2
*Anno : 2013/2014
*Corso : Informatica
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
  /*246 squadre, c'è anche la rappresentanza UNITN*/
  char *sq[] ={"Afghanistan",
    "Aland_Islands",
    "Albania",
    "Algeria",
    "American_Samoa",
    "Andorra",
    "Angola",
    "Anguilla",
    "Antarctica",
    "Antigua_And_Barbuda",
    "Argentina",
    "Armenia",
    "Aruba",
    "Australia",
    "Austria",
    "Azerbaijan",
    "Bahamas",
    "Bahrain",
    "Bangladesh",
    "Barbados",
    "Belarus",
    "Belgium",
    "Belize",
    "Benin",
    "Bermuda",
    "Bhutan",
    "Bolivia",
    "Bosnia_and_Herzegowina",
    "Botswana",
    "Bouvet_Island",
    "Brazil",
    "British_Indian_Territory",
    "Brunei_Darussalam",
    "Bulgaria",
    "Burkina_Faso",
    "Burundi",
    "Cambodia",
    "Cameroon",
    "Canada",
    "Cape_Verde",
    "Cayman_Islands",
    "Central_African_Republic",
    "Chad",
    "Chile",
    "China",
    "Christmas_Island",
    "Cocos_Keeling_Islands",
    "Colombia",
    "Comoros",
    "Congo",
    "Congo Republic",
    "Cook_Islands",
    "Costa_Rica",
    "Cote_d'Ivoire",
    "Croatia",
    "Cuba",
    "Cyprus",
    "Czech_Republic",
    "Denmark",
    "Djibouti",
    "Dominica",
    "Dominican_Republic",
    "Ecuador",
    "Egypt",
    "El_Salvador",
    "Equatorial_Guinea",
    "Eritrea",
    "Estonia",
    "Ethiopia",
    "Falkland_Islands_Malvinas",
    "Faroe_Islands",
    "Fiji",
    "Finland",
    "France",
    "French_Guiana",
    "French_Polynesia",
    "French_Territories",
    "Gabon",
    "Gambia",
    "Georgia",
    "Germany",
    "Ghana",
    "Gibraltar",
    "Greece",
    "Greenland",
    "Grenada",
    "Guadeloupe",
    "Guam",
    "Guatemala",
    "Guernsey",
    "Guinea",
    "Guinea-Bissau",
    "Guyana",
    "Haiti",
    "Heard_and_McDonald_Islands",
    "Vatican_City_State",
    "Honduras",
    "Hong_Kong",
    "Hungary",
    "Iceland",
    "India",
    "Indonesia",
    "Iran_Islamic_Republic_of",
    "Iraq",
    "Ireland",
    "Isle_of_Man",
    "Israel",
    "Italy",
    "Jamaica",
    "Japan",
    "Jersey",
    "Jordan",
    "Kazakhstan",
    "Kenya",
    "Kiribati",
    "Korea_Democratic",
    "Korea",
    "Kuwait",
    "Kyrgyzstan",
    "Lao",
    "Latvia",
    "Lebanon",
    "Lesotho",
    "Liberia",
    "Libyan_Arab_Jamahiriya",
    "Liechtenstein",
    "Lithuania",
    "Luxembourg",
    "Macao",
    "Macedonia",
    "Madagascar",
    "Malawi",
    "Malaysia",
    "Maldives",
    "Mali",
    "Malta",
    "Marshall_Islands",
    "Martinique",
    "Mauritania",
    "Mauritius",
    "Mayotte",
    "Mexico",
    "Micronesia",
    "Moldova_Republic_of",
    "Monaco",
    "Mongolia",
    "Montenegro",
    "Montserrat",
    "Morocco",
    "Mozambique",
    "Myanmar",
    "Namibia",
    "Nauru",
    "Nepal",
    "Netherlands",
    "Netherlands_Antilles",
    "New_Caledonia",
    "New_Zealand",
    "Nicaragua",
    "Niger",
    "Nigeria",
    "Niue",
    "Norfolk_Island",
    "Northern_Mariana",
    "Norway",
    "Oman",
    "Pakistan",
    "Palau",
    "Palestinian",
    "Panama",
    "Papua_New_Guinea",
    "Paraguay",
    "Peru",
    "Philippines",
    "Pitcairn",
    "Poland",
    "Portugal",
    "Puerto_Rico",
    "Qatar",
    "Reunion",
    "Romania",
    "Russian_Federation",
    "Rwanda",
    "Saint_Barthelemy",
    "Saint_Helena",
    "Saint_Kitts_and_Nevis",
    "Saint_Lucia",
    "Saint_Pierre_and_Miquelon",
    "Saint_Vincent",
    "Samoa",
    "San_Marino",
    "Sao_Tome_and_Principe",
    "Saudi_Arabia",
    "Senegal",
    "Serbia",
    "Seychelles",
    "Sierra_Leone",
    "Singapore",
    "Slovakia",
    "Slovenia",
    "Solomon_Islands",
    "Somalia",
    "South_Africa",
    "South_Georgia_Islands",
    "Spain",
    "Sri_Lanka",
    "Sudan",
    "Suriname",
    "Svalbard_and_Jan_Mayen",
    "Swaziland",
    "Sweden",
    "Switzerland",
    "Syrian_Arab_Republic",
    "Taiwan_Province_of_China",
    "Tajikistan",
    "Tanzania",
    "Thailand",
    "Timor-Leste",
    "Togo",
    "Tokelau",
    "Tonga",
    "Trinidad_and_Tobago",
    "Tunisia",
    "Turkey",
    "Turkmenistan",
    "Turks_and_Caicos_Islands",
    "Tuvalu",
    "Uganda",
    "Ukraine",
    "United_Arab_Emirates",
    "United_Kingdom",
    "United_States",
    "United_State_Islands",
    "Uruguay",
    "Uzbekistan",
    "Vanuatu",
    "Venezuela",
    "Viet_Nam",
    "Virgin_Islands",
    "Virgin_Islands_U.S.",
    "Wallis_and_Futuna",
    "Western_Sahara",
    "Yemen",
    "Zambia",
    "Zimbabwe",
    "Rappresentanza_UNITN" /* 246esima squadra, permette di non sforare gli indici */
	};
  /* apri il file di test in assets */
	FILE *f = fopen("assets/squadre.dat", "w"); //246squadre
	if (f == NULL){
	    printf("Errore nella lettura!\n");
	    exit(1);
	}

	srand(time(NULL));
	short i;
	for(i=0;i<246;i++){
		char *text = sq[i] ;//nome della squadra da scrivere
		
		short skill=rand()%10 +1;//genera skill casuali
		fprintf(f, "%s %d\n", text,skill);
	}
	fclose(f);

  f = fopen("assets/mondiali2014.dat", "w"); //32 squadre, quelle di Brazil 2014
  if (f == NULL){
      printf("Errore nella lettura!\n");
      exit(1);
  }

  char* mondiali="Brasile 10\nCroazia 5\nMessico 5\nCamerun 7\nSpagna  9\nOlanda  8\nCile 5\nAustralia 4\nColombia 4\nGrecia  4\nCosta_d'Avorio 7\nGiappone 4\nUruguay 7\nCosta_Rica 3\nInghilterra 6\nItalia 10\nSvizzera 4\nEcuador 5\nFrancia 7\nHonduras 5\nArgentina 9\nBosnia_Erzegovina 2\nIran 1\nNigeria 7\nGermania 9\nPortogallo  8\nGhana 7\nStati_Uniti 7\nBelgio 4\nAlgeria 2\nRussia 6\nCorea_del_Sud 5";
  fprintf(f, "%s", mondiali);
  
  fclose(f);

}