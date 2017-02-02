#include "kons.h"
#include "DB.h"
#include "autofax.h"

enum Txvg_ {
  T_VorgbSpeziell_Ueberlad,
  T_vgMAX,
};

class Txvgcl: public TxB
{
  public:
    static const char *TextC[][Smax];
    Txvgcl() {TCp=(const char* const * const * const *)&TextC;}
};

const char *Txvgcl::TextC[T_vgMAX+1][Smax]={
      // T_VorgbSpeziell_Ueberlad
      {"VorgbSpeziell_Ueberlad()","specificprefs_overload()"},
      {"",""}
};

class Txvgcl Txv;

void paramcl::VorgbSpeziell()
{
  Log(violetts+Txv[T_VorgbSpeziell_Ueberlad]+schwarz);
  //  langu="d"; lgnzuw();
  dbq="faxeinp";
  muser="praxis";
  citycode="8131";
  msn="616381";
  LocalIdentifier="DiabDachau";
  cFaxUeberschrift="Diabetologie Dachau";

  // wird schon fuer systemrueck benoetigt
  sqlz=sqlvz="7";
  const char *hatab = "haerzte_neu",
        *officetab = "office",
        *quelltab = "quelle",
        *kvaetab  = "kvaerzte";

  sqlzn=sqlvzn=atol(sqlvz.c_str());
  if (sqlvzn) {
//    sqlconfvp= new cppSchluess[sqlvzn];
    sqlconfv.neu(sqlvzn);
    for(size_t i=0;i<sqlvzn;i++) {
      sqlconfv[i].name=string("SQL_")+ltoan(i);
      switch (i) {
        case 0:
          sqlconfv[i].wert = string("")+"select if(isnull(arzt),bsname,arzt) getName,bsname from (select bsname, FaxZahl, "
            "concat(group_concat(distinct Arzt separator ', '), ', ',ort,';') Arzt "
            "from (SELECT bs.name bsname, f.faxzahl, concat(if(instr(Titel,'.')<>0,concat(left(titel,instr(titel,'.')),' '),Titel), "
            "left(a.Vorname,1), '.', a.Nachname, if(count(a.nachname)>6,'',concat(' (',group_concat(distinct "
            "replace(replace(replace(replace(replace(replace(replace(replace(replace(replace(replace(replace(replace(replace(replace(replace(replace"
            "(replace(replace(replace(replace(replace(replace(replace(replace(replace(if(isnull(fachrichtung),'',fachrichtung),"
            "'Facharzt für ','FA f.'),'Fachärztin für ','FÄ f.'),'Schwerpunkt',''),'edizin','ed.'),'Allgemeinmed.','Allgm.'),"
            "'therapeutische','th.'),'ologie','ol.'),'therapeutin','th.'),'therapeut','th.'),'heilkunde','hk.'),'therapie','th.'),"
            "'irurgie','ir.'),'pädie','p.'),'Jugendlichen','Jugdl.'),'Innere ','In.'),'krankheiten','krht.'),'hilfe','h.'),"
            "'Praktischer Arzt','Prakt.A.'),'Praktische Ärztin','Prakt.Ä.'),'Diagnostische ','diagn.'),'ologe','ol.'),"
            "'Hals-Nasen-Ohrenhk.','HNO'),'ologische ','ol.'),'ologischer ','ol.'),'istische','ist.'),'und ','u.') separator ', '),')'))) Arzt, "
            "ort.Ort "
            "from `"+hatab+"`.fax f left join `"+hatab+"`.arzt_has_bs ahb on f.bs_id = ahb.bs_id "
            "left join `"+hatab+"`.bs on f.bs_id = bs.idbs "
            "left join `"+hatab+"`.arzt a on ahb.arzt_id = a.idarzt "
            "left join `"+hatab+"`.arzt_has_fachrichtung ahf on ahb.arzt_id = ahf.arzt_id "
            "left join `"+hatab+"`.fachrichtung fr on ahf.fachrichtung_id = fr.idfachrichtung "
            "left join `"+hatab+"`.ort on bs.ort_id = ort.idort "
            "left join `"+hatab+"`.titel t on a.titel_id = t.idtitel where concat(if(mid(faxzahl,1,1)='0','','08131'),"
            "replace(replace(replace(replace(faxzahl,' ',''),'-',''),'/',''),'\\'','')) = '&&faxnr&&' "
            "group by faxzahl, nachname, vorname) i) i group by FaxZahl";
          break;
        case 1:
          sqlconfv[i].wert = string("")+"select concat(titel,if(titel='','',' '),vorname,' ',nvorsatz,if(nvorsatz='','',' '),nachname,', g.',"
            "date_format(gebdat,'%d.%m.%y'),', ',ort) name,concat('Pid ',pat_id) bsname from "+quelltab+".namen n where "
            "concat(if(mid(privatfax,1,1)='0','','08131'),replace(replace(replace(replace(privatfax,' ',''),'-',''),'/',''),"
            "'\\'','')) = '&&faxnr&&'";;
          break;
        case 2:
          sqlconfv[i].wert = string("")+"select concat(haname,', ',ort,', ',kvnu) name, zulg,fax1k from "+kvaetab+".hae where "
            "concat(if(mid(fax1k,1,1)='0','','08131'),replace(replace(replace(replace(fax1k,' ',''),'-',''),'/',''),'\\'','')) = " 
            "'&&faxnr&&'";
          break;
        case 3:
          sqlconfv[i].wert = string("")+"select concat(titel,if(titel='','',' '),vorname,' ',name,', ',ort) name, zusatzfeld5 from "+
            officetab+".adresse where concat(if(mid(faxk,1,1)='0','','08131'),replace(replace(replace(replace(faxk,' ',''),'-',''),'/',''),'\\'',''))"
            " = '&&faxnr&&' order by zusatzfeld5 desc";
          break;
        case 4:
          sqlconfv[i].wert = string("")+"SELECT concat(if(isnull(name),'',concat(titel,if(titel='','',' '),vorname,' ',name,', ',ort, ', ')),"
            "if(isnull(i.firma),'',i.firma)) name, i.abteilung FROM "+officetab+".telefon t left join "+officetab+".kontakte k "
            "on t.knr  = k.knr left join "+officetab+".pers p on k.knr = p.knr left join "+officetab+".inst i on k.knr = i.knr left join "+
            officetab+".anschr a on a.knr = p.knr where concat(if(mid(num,1,1)='0','','08131'),"
            "replace(replace(replace(replace(num,' ',''),'-',''),'/',''),'\\'',''))  = '&&faxnr&&' and (not isnull(name) "
            "or not isnull(firma) or not isnull(vorname)) order by name desc, vorname desc, firma desc";
          break;
        case 5:
          sqlconfv[i].wert = string("")+"select concat(titel,if(titel='','',' '),vorname,' ',nvorsatz,if(nvorsatz='','',' '),"
            "nachname,', g.',date_format(gebdat,'%d.%m.%y'),', ',ort) name,concat('Pid ',pat_id) bsname from "+quelltab+".namen n where "
            "concat(if(mid(privattel,1,1)='0','','08131'),replace(replace(replace(replace(privattel,' ',''),'-',''),'/',''),'\\'','')) = "
            "'&&faxnr&&'";
          break;
        case 6:
          sqlconfv[i].wert = string("")+"select concat(titel,if(titel='','',' '),vorname,' ',name) name,fachgruppe from "+quelltab+
            ".listenausgabeuew where concat(if(mid(fax,1,1)='0','','08131'),replace(replace(replace(replace(fax,' ',''),'-',''),'/',''),'\\'','')) "
            "= '&&faxnr&&'";
          break;
      }
    }
  }
  // cpt in VorgbAllg festgelegt
  if (strstr(cpt,"linux")){
//  host="localhost"; // 'localhost' schon Vorgabe bei Definition
    if (!strcmp(cpt,"linux2")) {
      zufaxenvz="/vista/P/zufaxen"; 
      wvz="/vista/P/warteauffax";
      nvz="/vista/P/nichtgefaxt";
      empfvz="/vista/P";
    } else {
      zufaxenvz="/DATA/Patientendokumente/zufaxen";
      wvz="/DATA/Patientendokumente/warteauffax";
      nvz="/DATA/Patientendokumente/nichtgefaxt";
      empfvz="/DATA/Patientendokumente";
    }
  } else {
    // if (!strcmp(cpt,"ANMELDL") || !strcmp(cpt,"SZSNEU"))
    //			host = "linux1";
    //			host = "[2001:a60:230a:7101:a0a7:25a1:a92:2a5e]";
    host = "192.168.178.21";
  }
  if (strstr(cpt,"linux")){
    if (!strcmp(cpt,"linux2")) {
      static zielmustercl zmi[]={zielmustercl("[Aa]rztbrief","/vista/P"),zielmustercl("","/vista/P/gefaxt")};
      zmvp=zmi;
      zmvzn=sizeof zmi/sizeof *zmi;
    } else { // linux1
      static zielmustercl zmi[]={zielmustercl("[Aa]rztbrief","/DATA/Patientendokumente"),zielmustercl("","/DATA/Patientendokumente/gefaxt")};
      zmvp=zmi;
      zmvzn=sizeof zmi/sizeof *zmi;
    }
  } else {
  }
} // void paramcl::VorgbSpeziell()

