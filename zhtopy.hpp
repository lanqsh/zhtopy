#ifndef ZHTOPY_H
#define ZHTOPY_H

/**
 * 汉字转拼音类
 * 1:汉字转拼音
 * 2:汉字转拼音简拼
 * 3:汉字转拼音首字母
 */

#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
#include <iconv.h>
#include <regex>

/*
// example

// 汉字转拼音 zhongwen
std::string pinyin = ZhToPY::instance()->zhToPY("中文");

// 汉字转字母简拼 ZW
std::string jinpin = ZhToPY::instance()->zhToJP("中文");

// 汉字转首字母 Z
std::string shouzimu = ZhToPY::instance()->zhToZM("中文");
*/

class ZhToPY
{
    public:
        static ZhToPY *instance();
        explicit ZhToPY();

    private:
        static ZhToPY *self;
        std::vector<std::string> listPY;
        std::string listStrJP;

    public:
        //汉字转拼音
        std::string zhToPY(const std::string &chinese);
        //汉字转字母简拼
        std::string zhToJP(const std::string &chinese);
        //汉字转首字母
        std::string zhToZM(const std::string &chinese);
};

typedef unsigned short ushort;

static std::string pinyinArrStr =
"yi ding yu qi shang xia myeon wan zhang san shang xia qi bu yu mian gai chou chou zhuan qie pi shi shi qiu bing ye cong dong si cheng diu qiu liang diu you liang yan bing sang shu jiu ge ya pan zhong ji "
"jie feng guan chuan chan lin zhuo zhu ha wan dan wei zhu jing li ju pie fu yi yi nai wu jiu jiu tuo mo yi ho zhi wu zha hu fa le yin ping pang qiao hu guai cheng cheng yi yin ya mie jiu qi ye xi xiang "
"gai jiu hal hol shu dou shi ji keg kal keol tol mol ol mai luan cal ru xue yan phoi sal na gan sol eol cui ceor gan luan gui gan luan lin yi jue le ma yu zheng shi shi er chu yu kui xu yun hu qi wu jing "
"si sui gen geng ya xie ya zhai ya ji wen wang kang da jiao hai yi chan heng mu ye xiang jing ting liang xiang jing ye qin bo you xie zhan lian duo wei ren ren ji ra wu yi shen ren li ding ze jin pu chou "
"ba zhang jin ge bing reng cong fo jin lun bing cang zai shi ta zhang fu xian xian tuo hong tong ren qian han yi bo dai ling yi chao zhang sa shang yi mu men ren fan chao yang jing zhong bi wo wu jian jia "
"yao feng cang ren wang fen di fang zhong qi pei yu diao dun wu yi xin kang yi ji ai wu qi fu fa xiu jin pi shen fu tang zhong you huo hui yu cui yun san wei chuan ju ya xian shang chang lun cang xun xin "
"wei zhu chi xuan nu bo gu ni ni xie ban xu ling zhou shen qu ci peng si jia pi zhi shi yi zheng dian gan mai dan zhu bu qu bi zhao ci wei di zhu zuo you yang ti zhan he bi tuo she yu die fo zuo gou ning "
"tong ni xian qu yong wa qian shi ka bao pei hui ge lao xiang ge yang bai fa ming jia er bing ji hen huo gui quan tiao jiao ci yi shi xing shen tuo kan zhi hai lai yi chi kua guang li yin shi mi zhu xu "
"you an lu mou er lun dong cha chi xun gong zhou yi ru cun xia si dai lv ta jiao zhen ce qiao kuai chai ning nong jin wu hou jiong cheng chen zuo chou qin lv ju dou ting shen tui bo nan xiao bian tui yu "
"xi cu e qiu xu guang ku wu jun yi fu liang zu qiao li yong hun jing xian san pei su fu xi li mian ping bao yu si xia xin xiu yu di ju chou zhi yan liang li lai si jian xiu fu huo ju xiao pai jian biao "
"shu fei feng ya an bei yu xin bei hu chang zhi bing jiu yao cui liang wan lai cang zong ge guan bei tian shu shu men dao dan jue chui xing peng tang hou yi qi ti gan jing jie sui chang jie fang zhi kong "
"juan zong ju qian ni lun zhuo wo luo song ling hun dong zi ben wu ju nai cai jian zhai ye zhi sha qing qie ying cheng qian yan ru zhong chun jia jie wei yu bing ruo ti wei pian yan feng dang wo e xie che "
"sheng kan di zuo cha ting bei ye huang yao zhan chou an you jian xu zha ci fu fu zhi cong mian ji yi xie xun si duan ce zhen ou tou tou bei zan lou jie wei fen chang kui sou si su xia fu yuan rong li nu "
"yun gou ma pang dian tang hao jie xi shan qian que cang chu san bei xiao rong yao ta suo yang fa bing jia dai zai tang gu bin chu nuo can lei cui yong cao zong beng song ao chuan yu zhai qi shang chuang "
"jing chi sha han zhang qing yan di xie lou bei piao jin lian lu man qian xian tan ying dong zhuan xiang shan qiao jiong tui zun pu xi lao chang guang liao qi deng chan wei ji bo hui chun tie dan jiao jiu "
"ceng fen xian ju e jiao jian tong lin bo gu xian su xian jiang min ye jin jia qiao pi feng zhou ai sai yi jun nong tan yi dang jing xuan kuai jian chu dan jiao sha zai can bin an ru tai chou chai lan yi "
"jin qian meng wu ning qiong ni chang lie lei lv kuang bao yu biao zan zhi si you hao qing qin li teng wei long chu chan rang shu xie li luo zan nuo tang yan lei nang er wu yun zan yuan xiong chong zhao "
"xiong xian guang yue ke dui mian tu chang er dui er jin tu si yan yan shi shike dang qianke dou gongfen haoke shen dou baike jing gongli huang ru wang nei quan liang yu ba gong liu xi jie lan gong tian "
"guan xing bing qi ju dian ci ppun yang jian shou ji yi ji chan tong mao ran nei yan mao gang ran ce jiong ce zai gua jiong mao zhou mao gou xu mian tu rong yin xie kan jun nong yi mi shi guan meng zhong "
"ju yuan ming kou min fu xie mi liang dong tai gang feng bing hu chong jue ya kuang ye leng pan fa min dong xian lie qia jian jing sou mei tu qi gu zhun song jing liang qing diao ling dong gan jian yin "
"cou ai li cang ming zhun cui si duo jin lin lin ning xi du ji fan fan fan feng ju chu zheng feng mu zhi fu feng ping feng kai huang kai gan deng ping qian xiong kuai tu ao chu ji dang han han zao dao "
"diao li ren ren chuang fen qie yi ji kan qian cun chu wen ji dan xing hua wan jue li yue lie liu ze gang chuang fu chu qu diao shan min ling zhong pan bie jie jie pao li shan bie chan jing gua geng dao "
"chuang kui kuo duo er zhi shua quan sha ci ke jie gui ci gui kai duo ji ti jing dou luo ze yuan cuo xiao ke la qian sha chuang gua jian cuo li ti fei pou chan qi chuang zi gang wan bo ji duo qing yan "
"zhuo jian ji bo yan ju huo sheng jian duo duan wu gua fu sheng jian ge da kai chuang chuan chan zhuan lu li peng shan piao kou jiao gua qiao jue hua zha zhuo lian ju pi liu gui chao gui jian jian tang "
"huo ji jian yi jian zhi chan zuan mi li zhu li ya quan ban gong jia wu mai lie jin keng xie zhi dong zhu nu jie qu shao yi zhu miao li jin lao lao juan kou gu wa xiao mou kuang jie lie he shi ke jin gao "
"bo min chi lang yong yong mian ke xun juan qing lu bu meng chi lei kai mian dong xu xu kan wu yi xun weng sheng lao mu lu piao shi ji qin qiang jiao quan xiang yi qiao fan juan tong ju dan xie mai xun "
"xun lv li che xiang quan bao di yun jiu bao gou wu yun mangmi bi gai gai bao cong yi xiong peng ju tao ge pu e pao fu gong da jiu gong bi hua bei nao chi fang jiu yi za jiang kang jiang kuang hu xia qu "
"fan gui qie cang kuang fei hu yu gui gui hui dan gui lian lian suan du jiu qu xi pi qu yi ke yan bian ni qu shi xun qian nian sa zu sheng wu hui ban shi xi wan hua xie wan bei zu zhuo xie dan mai nan dan "
"ji bo shuai bu guan bian bu zhan ka lu you lu xi gua wo xie jie ran wei ang qiong zhi mao yin wei shao ji que luan chi juan xie xu jin que kui ji e qing xi san chang yan e ting li zhai an li ya ya ya she "
"di zhai pang ting qie ya shi ce mang ti li she hou ting zui cuo fei yuan ce yuan xiang yan li jue xia dian chu jiu jin ao gui yan si li chang qian li yan yan yuan si hong miao qiu qu qu keum lei du xian "
"zhuan san can can can can ai dai you cha ji you shuang fan shou guai ba fa ruo shi shu zhuo qu shou bian xu xia pan sou ji wei sou die rui cong kou gu ju ling gua dao kou zhi jiao zhao ba ding ke tai chi "
"shi you qiu po ye hao si tan chi le diao ji dug hong mie xu mang chi ge song yao ji he ji diao cun tong ming hou li tu xiang zha xia ye lv ya ma ou huo yi jun chou lin tun yin fei bi qin qin jie bu fou "
"ba dun fen hua han ting hang shun qi hong zhi yin wu wu chao na jue xi chui dou wen hou ou wu gao ya jun lv e ge wen dai qi cheng wu gao fu jiao yun chi sheng na tun mu yi tai ou li bei yuan wo wen qiang "
"wu e shi juan pen min ne mu ling ran you di zhou shi zhou tie xi yi zhi ping ci gua ci wei hou he nu xia pei chi hao shen hu ming dan qu zui gan za tuo duo pou pao bi fu yang he zha he tai jiu yong fu da "
"zhou wa ka gu ka zuo bu long dong ning tuo si xian huo qi er e guang zha die yi lie zi mie mie zhi yao ji zhu lo xun za xiao ke hui kua shi tiao xian an xuan xiu guo yan lao yi ai pin shen tong hong "
"xiong duo wa ha zai you di pai xiang ai hen kuang ya da xiao bi hui nian hua xing kuai duo ppun ji nong mou yo hao yuan long tou mang ge o chi shao li na zu he ku xiao xian lao bo zhe zha lang ba mie lie "
"sui fu bu han heng geng shuo jia you yan gu gu bei han suo chun yi ai jia tu yan wan li xi tang zuo qiu che wu zao ya dou qi di qin mai mas gong teo keos lao liang suo zao huan lang sha ji zo wei feng "
"jin hu qi shou wei shua chang er li qiang an zuo yo nian yu tian lai qie xi tuo hu ai zhou nou ken zhuo zhao shang di heng lin a cai qiang tun wu wen cui jie gu qi qi tao dan dan ye ci bi cui chuo he ya "
"qi zhe fei liang xian pi sha la ze qing gua pa ze se zhuan nie guo luo ngam di quan chan bo ding lang xiao geu tang di ti an jiu dan ke yong wei nan shan yu zhe la jie hou han die zhou chai wai nuo yu "
"yin za yao wo mian hu yun chuan hui huan yuan xi he ji kui zhong wei che xu huang duo yan xuan liang yu sang chi qiao yan dan ben qi li yo zha wei miao ying pen phos kui bei yu gib lou ku qiao hu ti yao "
"he sha xiu qiang se yong su gong xie yi shuo ma cha hai ke da sang tian ru sou gu ji pang wu qian shi ge zi jie lao weng wa si chi hao suo jia hai suo qin nie he cis sai en go na dia ai qiang tong bi ao "
"ao lian zui zhe mo shu sou tan di qi jiao chong dao kai tan shan cao jia ai xiao piao lou ga jia xiao hu hui guo ou xian ze chang xu po de ma ma hu le du ga tang ye beng ying sai jiao mi xiao hua mai ran "
"zuo peng lao xiao ji zhu chao kui zui xiao si hao mu liao qiao xi xu tan tan hei xun e zun bo chi hui can chuang cu dan yu tun ceng jiao ye xi qi hao lian xu deng hui yin pu jue qin xun nie lu si yan "
"ying da zhan ao zhuo jin nong hui xie qi e zao ai shi jiao yuan ai yong xue kuai yu pen dao ge xin dun dang xin sai pi pi yin zui ning di lan ta huo ru hao xia yan duo pi chou ji jin hao ti chang xun me "
"ca ti lu hui bao you nie yin hu mo hong zhe li liu xie nang xiao mo yan li lu long po dan chen pin pi xiang huo me xi duo ku yan chan ying rang di la ta xiao jiao chuo huan huo zhuan nie xiao za li chan "
"chai li yi luo nang zan su heui zeng jian yan zhu lan nie nang ram luo wei hui yin qiu si nin nan hui xin yin nan tuan tuan tun kang yuan jiong pian yun cong hu hui yuan e guo kun cong wei tu wei lun guo "
"qun shi ling gu guo tai guo tu you guo yin hun pu yu han yuan lun quan yu qing guo chuan wei yuan quan ku pu yuan yuan ya tuan tu tu tuan lue hui yi huan luan luan tu ya tu ting ku pu lu kuai ya zai xu "
"ge zhun wu gui pi yi di qian qian zhen zhuo dang qia xia shan kuang chang qi nie mo ji jia zhi zhi ban xun yi qin fen jun rong tun fang fen ben tan kan huai zuo kang bi jing di jing ji kuai di jing jian "
"tan li ba wu fen zhui po ban tang kun ju tan zhi tuo gan ping dian gua ni tai pi jiong yang fo ao lu qiu mu ke gou xue ba di che ling zhu fu hu zhi chui la long long lu ao dai pao min xing tong ji he lv "
"ci chi lei gai yin hou dui zhao fu guang yao duo duo gui cha yang yin fa gou yuan die xie ken jiong shou e bing dian hong ya kua da ka dang kai hang nao an xing xian yuan bang fu bei yi yin han xu zhui "
"cen geng ai feng fang jue yong jun xia di mai lang juan cheng yan qin zhe lie lie bu cheng hua bu shi xun guo jiong ye dian di yu bu ya juan sui pi qing wan ju lun zheng kong shang dong dai tan yan cai "
"chu beng xian zhi duo yi zhi yi pei ji zhun qi sao ju ni ku ke tang kun ni jian dui jin gang yu e peng gu tu leng fang ya qian kun an shen duo nao tu cheng yin hun bi lian guo die zhuan hou bao bao yu di "
"mao jie ruan ye geng kan zong yu huang e yao yan bao ji mei chang du tuo yin feng zhong jie jin feng gang chuan jian ping lei jiang huang leng duan wan xuan ji ji kuai ying ta cheng yong kai su su shi mi "
"ta weng cheng tu tang qiao zhong li peng bang sai zang dui tian wu zheng xun ge zhen ai gong yan kan tian yuan wen xie liu hai lang chang peng beng chen lu lu ou qian mei mo zhuan shuang shu lou chi man "
"biao jing ce shu zhi zhang kan yong dian chen zhi ji guo qiang jin di shang mu cui yan ta zeng qian qiang liang wei zhui qiao zeng xu shan shan fa pu kuai dong fan qiao mo dun dun zun di sheng duo duo "
"tan deng wu fen huang tan da ye zhu jian ao qiang ji qiao ken yi pi bi dian jiang ye yong xue tan lan ju huai dang rang qian xun lan xi he ai ya dao hao ruan jin lei kuang lu yan tan wei huai long long "
"rui li lin rang chan xun yan lei ba wan shi ren san zhuang zhuang sheng yi mai ke zhu zhuang hu hu kun yi hu xu kun shou mang dun shou yi zhi ying chu jiang feng bei zhai bian sui qun ling fu cuo xia "
"xiong xie nao xia kui xi wai yuan mao su duo duo ye qing oes gou gou qi meng meng yin huo chen da ce tian tai fu jue yao yang hang gao shi ben tai tou tao bi yi kua jia duo hwa kuang yun jia ba en lian "
"huan di yan pao juan qi nai feng xie fen dian juan kui zou huan qi kai zha ben yi jiang tao zhuang ben xi huang fei diao xun beng dian ao she weng tai ao wu ao jiang lian duo yun jiang shi fen huo bi "
"luan che nv nu ding nai qian jian ta jiu nuan cha hao xian fan ji shuo ru fei wang hong zhuang fu ma dan ren fu jing yan jie wen zhong pa du ji hang zhong yao jin yun miao pei chi jue zhuang niu yan na "
"xin fen bi yu tuo feng yuan fang wu yu gui du ba ni zhou zhuo zhao da ni yuan tou xuan yi e mei mo qi bi shen qie e he xu fa zheng min ban mu fu ling zi zi shi ran han yang gan jie gu si xing wei ci ju "
"shan pin ren yao dong jiang shu ji gai xiang huo juan jiao gou lao jian jian yi nian zhi zhen ji xian heng guang xun kua yan ming lie pei ya you yan cha xian yin ti gui quan zi song wei hong wa lou ya "
"rao jiao luan pin xian shao li cheng xie mang fu suo mu wei ke cu cu ting niang xing nan yu na pou sui juan shen zhi han di zhuang e ping tui xian mian wu yan wu ai yan yu si yu wa li xian ju qu zhui qi "
"xian zhuo dong chang lu ai e e lou mian cong pei ju po cai ling wan biao xiao shu qi hui fan wo rui tan fei fei jie tian ni juan jing hun jing jin dian xing hu guan lai bi yin chou chuo fu jing lun an "
"lan kun yin ya ju li dian xian hua hua ying chan shen ting yang yao mu nan ruo jia yu xu yu wei ti rou mei dan ruan qin hui wo qian chun miao fu jie duan pei zhong mei huang mian an ying xuan jie wei mei "
"yuan zheng qiu ti xie tuo lian mao ran si pian wei wa cu hu yun jie bao xu yu gui zou yao bi xi yuan ying rong ru chi liu mei pan yun ma gou kui qin jia sao zhen yuan jie rong ming ying ji su niao xian "
"tao pang lang nao bao ai pi pin yi piao yu lei xuan yuan yi zhang kang yong ni li di gui yan jin zhuan chang ce han nen lao mo zhe hu hu ao nen qiang ma pie gu wu qiao tuo zhan miao xian xian mo liao "
"lian hua gui deng zhi xu yi hua xi kui yao xi yan chan jiao mei fan fan yan yi hei jiao fan shi bi chan sui qiang lian huan xin niao dong yi can ai niang ning ma tiao chou jin ci yu pin rong ru nai yan "
"tai ying qian niao yue ying mian bi ma shen xing ni du liu yuan lan yan shuang ling jiao niang lan xian ying shuang xie huan mi li luan yan shu lan zi jie jue jue kong yun zi zi cun sun fu bo zi xiao "
"shen meng si tai bao ji gu nu xue you zhuan hai luan sun nao mie cong qian shu chan ya zi yi fu zi li xue bo ru nai nie nie ying luan mian ning rong ta gui zhai qiong yu shou an tu song wan rou yao hong "
"yi jing zhun mi zhu dang hong zong guan zhou ding wan yi bao shi shi chong shen ke xuan shi you huan yi tiao shi xian gong cheng jiong gong xiao zai zha bao hai yan xiao jia pan chen rong huang mi kou "
"kuan bin su cai zan ji yuan ji yin mi kou qing he zhen jian fu ning bing huan mei qin han yu shi ning qin ning zhi yu bao kuan ning qin mo cha lou gua qin hu wu liao shi ning zhai shen wei xie kuan hui "
"liao jun huan yi yi bao qin chong bao feng cun dui si xun dao luo dui shou po feng zhuan fu she ke jiang jiang zhuan wei zun xun shu dui dao xiao jie shao er er er ga jian shu chen shang shang ma ga "
"chang liao xian xian kun you you you liao liao yao long wang wang wang ga yao duo kui zhong jiu gan gu gan tui gan gan shi yin chi kao ni jin wei niao ju pi ceng xie bi ju jie tian jue ti jie wu diao shi "
"shi ping ji xie zhen xie ni zhan xi u man e lou ping ti fei shu xie tu lv lv xi ceng lv ju xie ju jue liao jue shu xie che tun ni shan wa xian li yan dao hui hong yi qi ren wu an shen yu chu sui qi yen "
"yue ban yao ang ya wu jie ji ji qian fen wan qi cen qian qi cha jie qu gang xian ao lan dao ba zuo zuo yang ju gang ke gou xue po li tiao zu yan fu xiu jia ling tuo pi ao dai kuang yue qu hu po min an "
"tiao ling chi ping dong ceom kui bang mao tong xue yi bian he ba luo e fu xun die lu en er gai quan tong yi mu shi an wei huan zhi mi li ji tong wei you gu xia lie yao qiao zheng luan jiao e e yu ye bu "
"qiao qun feng feng nao li you xian rong dao shen cheng tu geng jun gao xia yin wu lang kan lao lai xian que kong chong chong ta lin hua ju lai qi min kun kun cui gu cui ya ya gang lun lun ling jue duo "
"zheng guo yin dong han zheng wei xiao bi yan song jie beng cui jue dong chan gu yin zi ze huang yu wei yang feng qiu yang ti yi zhi shi zai yao e zhu kan lv yan mei han ji ji huan ting sheng mei qian "
"mao yu zong lan jie yan yan wei zong cha sui rong ke qin yu qi lou tu cui xi weng cang tang ying jie ai liu wu song qiao zi wei beng dian cuo qian yong nie cuo ji shi ruo song zong jiang liao kang chan "
"di cen ding tu lou zhang zhan zhan ao cao qu qiang wei zui dao dao xi yu pei long xiang ceng bo qin jiao yan lao zhan lin liao liao jin deng duo zun qiao jue yao jiao yao jue zhan yi xue nao ye ye yi "
"nie xian ji jie ke xi di ao zui wei yi rong dao ling jie yu yue yin ru jie li xi long long dian ying xi ju chan ying wei yan wei nao quan chao cuan luan dian dian nie yan yan yan kui yan chuan kuai "
"chuan zhou huang jing xun chao chao lie gong zuo qiao ju gong keo wu pu pu cha qiu qiu ji yi si ba zhi zhao xiang yi jin sun quan phas xun jin fu za bi shi bu ding shuai fan nie shi fen pa zhi xi hu dan "
"wei zhang nu dai mo pi pa tie fu lian zhi zhou bo zhi di mo yi yi ping qia juan ru shuai dai zhen shui qiao zhen shi qun xi bang dai gui chou ping zhang jian wan dai wei chang qie qi ce guo mao zhu hou "
"zhen zheng mi wei wo fu kai bang ping die gong pan huang tao mi jia teng hui zhong shen man mu biao guo ce mu bang zhang jing chan fu zhi wu fan chuang bi bi zhang mi qiao chan fen meng bang chou mie "
"chu jie xian lan gan ping nian jian bing bing xing gan yao huan you you ji guang bi ting ze guang zhuang mo qing pi qin tun chuang gui ya ting jie xu lu wu zhuang ku ying di pao dian ya miao geng ci fu "
"tong pang fei xiang yi zhi tiao zhi xiu du zuo xiao tu gui ku pang ting you bu bing cheng lai bei cuo an shu kang yong tuo song shu qing yu yu miao sou ce xiang fei jiu e gui liu xia lian lang sou zhi "
"bu qing jiu jiu jin ao kuo lou yin liao dai lu yi chu chan tu si xin miao chang wu fei guang kos kuai bi qiang xie lin lin liao lu ji ying xian ting yong li ting yin xun yan ting di po jian hui nai hui "
"gong nian kai bian yi qi nong fen qu nan yi zang bi yi yi er san shi er shi shi gong diao yin hu fu hong wu di chi jiang ba shen di zhang jue tao fu di mi xian hu chao nu jing zhen yi mi juan wan shao "
"ruo yuan jing diao zhang jiang qiang peng dan qiang bi bi she dan jian gou ge fa bi kou jian bie xiao dan guo jiang hong mi kuo wan jue ji ji gui dang lu lu tuan hui zhi hui hui yi yi yi yi huo huo xian "
"xing wen tong yan yan yu chi cai biao diao bin peng yong piao zhang ying chi chi zhuo tuo ji fang zhong yi wang che bi di ling fu wang zheng cu wang jing dai xi xun hen yang hui lv hou jia cheng zhi xu "
"jing tu cong cong lai cong de pai xi uu ji chang zhi cong zhou lai yu xie jie jian shi jia pian huang fu xun wei pang yao wei xi zheng biao chi de zheng zheng bie de chong che jiao hui jiao hui mei long "
"xiang bao qu xin xin bi yi le ren dao ting gai ji ren ren qian tan te te han qi tai cun zhi wang mang xi fan ying tian min min zhong chong wu ji wu xi jie you wan cong song kuai yu bian qi shi cui chen "
"tai zhun qin nian hun xiong niu wang xian xin hang hu kai fen huai tai song wu ou chang chuang ju yi bao chao min pei zha zen yang ju ban nu nao zheng pa bu zhan hu hu ju dan lian si you di dai yi die "
"you fu ji peng xing yuan ni guai fei xi bi yao qie xuan cong bing huang xu chu bi shu xi tan yong zong dui mo ki yi shi nen xun zhi xi lao heng kuang mou zhi xie lian tiao huang die hao kong wei heng qi "
"jiao shu si kua qiu yang hui hui chi qi yi xiong guai lin hui zi xu chi shang nv hen en ke dong tian gong zhuan xi qia yue peng ken de hui e xiao tong yan kai ce nao yun mang yong yong juan bi kun qiao "
"yue yu yu jie xi zhe lin ti han hao qie ti bu yi qian hui xi bei men yi heng song xun cheng li wu wu you li liang huan cong nian yue li nin nao e que xuan qian wu min cong fei bei de cui chang men li ji "
"guan guan xing dao qi kong tian lun xi kan gun ni qing chou dun guo zhan jing wan yuan jin ji lin yu huo he juan tan ti ti nian wang chuo hu hun xi chang xin wei hui e rui zong jian yong dian ju can "
"cheng de bei qie can dan guan duo nao yun xiang chuan die huang chun qiong re xing ce bian min zong shi qiao chou bei xuan wei ge qian wei yu yu bi xuan huan min bi yi mian yong he yang yin e chen mao "
"ke ke yu ai qie yan ruan gan yun cong si leng fen ying kui kui que gong yun su su qi yao song huang ji gu ju chuang ni xie kai zheng yong cao xun shen bo kai yuan xi hun yong yang li sao tao yin ci chu "
"qian tai huang yun shen ming gong she cao piao mu mu guo chi can can can cui min ni zhang tong ao shuang man guan que zao jiu hui kai lian ou song jin yin lv shang wei tuan man qian she yong qing kang di "
"zhi lou juan qi qi yu ping liao cong you chong zhi tong cheng qi qu peng bei bie qiong jiao zeng chi lian ping kui hui qiao cheng yin yin xi xi dan tan duo dui dun su jue ce xiao fan fen lao lao chong "
"han qi xian min jing liao wu can jue cu xian tan sheng pi yi chu xian nang dan tan jing song han ji wei huan dong qin qin ju cao ken xie ying ao mao yi lin se jun huai men lan ai lin yan guo xia chi yu "
"yin dai meng yi meng dui qi mo xian men chou zhi nuo nuo yan yang bo zhi kuang kuang you fu liu mie cheng hui chan meng lan huai xuan rang chan ji ju huan she yi lian nan mi tang jue gang gang gang ge "
"yue wu jian xu shu rong hu cheng wo jie ge can qiang huo qiang zhan dong qi jia die cai jia ji zhi kan ji kui gai deng zhan chuang ge jian jie yu jian yan lu xi zhan xi xi chuo dai qu hu hu hu e yi ti "
"mao hu li fang suo bian dian jiong shang yi yi shan hu fei yan shou ti cai zha qiu le pu pa da reng fu ru zai tuo zhang diao kang yu wu han shen cha tuo ge kou wu den qian zhi ren kuo men sao yang niu "
"ban che rao xi qin ban jia yu fu ao zhe pi zhi kan e den zhao cheng ji yan wang bian chao gou wen gu yue jue ba qin shen zheng yun wan ne yi shu zhua pou dou dou kang zhe fu fu pao ba ao ze zhuan kou "
"lun qiang yun hu bao bing zhai peng nan bu pi tai yao zhen zha yang bao he ni ye di chi pi jia ma mei shen ya chou qu min chu jia fu zha zhu dan chai mu dian la fu pao ban pai ling na guai qian ju tuo "
"ba tuo tuo ao ju zhuo pin zhao bai bai zhi ni ju kuo long jian qia yong lan ning bo ze qian hen kuo shi jie zheng nin gong gong quan quan cun zan kao yi xie ce hui pin zhuai shi na bai chi gua zhi guang "
"duo duo zhi qia an nong zhen ge jiao kua dong na tiao lie zha lu she wa jue lie ju zhi luan ya wo ta jia nao dang jiao zheng ji hui xian yu ai tuo nuo cuo bo geng ti zhen cheng suo suo keng mei nong ju "
"bang jian yi ting yan nuo wan jia cha feng ku wu jun ju tong kun chi tu zhuo fu luo ba han shao nie juan ze shu ye jue bu wan bu zun zhuai zhai lu sou shui lao sun bang jian huan dao wei wan qin peng "
"she lie min men fu ba ju dao luo ai juan yue song tian chui jie tu ben na niane wei cu wo qi xian cheng dian sao lun qing gang zhuo shou diao pou di zhang hun ji tao qia qi pai shu qian ling ye ya jue "
"zheng liang gua nie huo yan ding lue cai tan che bing jie ti kong tui yan cuo zhou ju tian qian ken bai pa jie lu guo ming geng zhi dan meng can sao guan peng chuan nuo jian zheng you qian yu yan kui "
"nan xuan rou che wei sai zou xuan miao ti nie cha shi song zhen yi xun huang bian yang huan yan zan an xu ya wo ke chuai ji di la la cheng kai jiu jiu tu jie hui gen chong xiao ye xie yuan jian ye cha "
"zha bei yao wei dem lan wen qin chan ge lou zong gen jiao gou qin rong que zou chi zhan sun sun bo chu rong bang cuo sao ke yao dao zhi nuo xie jian sou qiu gao xian shuo sang jin mie yi chui nuo shan "
"ta jie tang pan ban da li tao hu zhi wa xia qian wen qiang shen zhen e xie na quan cha zha ge wu en she gang she lu bai yao bin rong tan sha chan suo liao chong chuang guo bing feng shuai di ji sou zhai "
"lian cheng chi guan lu luo lou zong gai hu zha cheng tang hua cui zhi mo qiang gui ying zhi ao zhi che man chan kou chu she tuan chao mo mo zhe chan qian piao jiang yao gou qian liao ji ying jue pie pie "
"lao dun xian ruan gui zen yi xun cheng cheng sa nao hong si han guang da zun nian lin cheng wei zhuang jiao ji cao tan dan che bo che jue xiao liao ben fu qiao bo cuo zhuo zhuan zhui pu qin dun nian hua "
"xie lu jiao cuan ta han ji wo jian gan yong lei nang lu shan zhuo ze bu chuo ji dang se cao qing qing huan jie qin kuai dan xie ye pi bo ao ju ye e meng sou mi ji tai zhuo dao xing lan ca ju ye ru ye ye "
"ni huo jie bin ning ge zhi jie kuo mo jian xie lie tan bai sou lu li rao zhi pan yang lei ca lu cuan nian xian jun huo li lai huan ying lu long qian qian zan qian lan xian ying mei rang chan ying cuan "
"xie she luo mei mi chi zan luan tan zuan li dian wa dang jiao jue lan li nang zhi gui gui qi xun pu pu shou kao you gai yi gong gan ban fang zheng po dian kou min wu gu he ce xiao mi shou ge di xu jiao "
"min chen jiu zhen dui yu chi ao bai xu jiao dui lian nie bi chang dian duo yi gan san ke yan dun qi tou xue duo qiao jing yang xia min shu ai qiao ai zheng di chen fu shu liao ou xiong yi jiao shan jiao "
"zhuo yi lian bi li xiao xiao wen xue qi qi zhai bin jue zhai uu fei ban ban lan yu lan men dou sheng liao jia hu xie jia yu zhen jiao wo tou dou jin chi yin fu qiang zhan qu zhuo zhan duan zhuo si xin "
"zhuo zhuo qin lin zhuo chu duan zhu fang jie hang yu shi pei you myeo pang qi zhan mao lv pei pi liu fu fang xuan jing jing ni zu zhao yi liu shao jian eos yi qi zhi fan piao fan zhan kuai sui yu wu ji "
"ji ji huo ri dan jiu zhi zao xie tiao xun xu ga la han han ying di xu chan shi kuang yang shi wang min min tun chun wu yun bei ang ze ban jie kun sheng hu fang hao jiong chang xuan ming hun fen qin hu "
"yi xi cuan yan ze fang tan shen ju yang zan bing xing ying xuan po zhen ling chun hao mei zuo mo bian xiong hun zhao zong shi shi yu fei yi mao ni chang wen dong ai bing ang zhou long xian kuang tiao "
"chao shi huang huang xuan kui kua jiao jin zhi jin shang tong hong yan gai xiang shai xiao ye yun hui han han jun wan xian kun zhou xi sheng sheng bu zhe zhe wu wan hui hao chen wan tian zhuo zui zhou "
"pu jing xi shan ni xi qing qi jing gui zheng yi zhi yan wan lin liang chang wang xiao zan fei xuan geng yi xia yun hui xu min kui ye ying du wei shu qing mao nan jian nuan an yang chun yao suo pu ming "
"jiao kai gao weng chang qi hao yan li ai ji ji men zan xie hao mu mo cong ni zhang hui bao han xuan chuan liao xian tan jing pie lin tun xi yi ji huang dai ye ye li tan tong xiao fei shen zhao hao yi "
"xiang xing shan jiao bao jing yan ai ye ru shu meng xun yao pu li chen kuang die uu yan huo lu xi rong long nang luo luan shai tang yan zhu yue yue qu ye geng yi hu he shu cao cao sheng man zeng zeng "
"ti zui jian xu hui yin qie fen pi yue you ruan peng ban fu ling ku xu uu nv tiao shuo zhen lang lang juan ming huang wang tun chao qi qi ying zong wang tong lang lao meng long mu pin wei mo ben zha zhu "
"shu teul zhu ren ba pu duo duo dao li qiu ji jiu bi xiu cheng ci sha ru za quan qian yu gan wu cha shan xun fan wu zi li xing cai cun ren shao tuo duo zhang mang chi yi ge gong du yi qi shu gang tiao "
"jiang shan wan lai jiu mang yang ma miao zhi yuan hang bei bei jie dong gao yao qian chu chun pa shu hua xin niu zhu chou song ban song ji yue jin gou ji mao pi bi wang ang fang fen yi fu nan xi hu ya "
"dou xin chen yao lin nen e mei zhao guo zhi cong yun zui sheng shu zao duo li lu jian cheng song qiang feng zhan xiao zhen ku ping tai xi zhi guai xiao jia jia gou bao mo xie ye ye shi nie bi tuo yi "
"ling bing ni la he ban fan zhong dai ci yang fu bo mou gan qi ran rou mao shao song zhe xia you shen ju tuo zuo ran ning yong chi zhi zu cha dan gu bu jiu ao fu jian ba duo ke nai zhu bi liu chai zha si "
"zhu pei shi guai cha yao cheng jiu shi zhi liu mei li rong zha zao biao zhan zhi long dong lu saeng li lan yong shu xun shuan qi chen xi li yi xiang zhen li ci kuo kan bing ren xiao bai ren bing zi chou "
"yi ci xu zhu zun zui er er you fa gong kao lao zhan lie yin yang he gen zhi shi ge zai luan fu jie heng gui tao guang wei kuang ru an an juan yi zhuo ku zhi qiong tong sang sang huan ju jiu xue duo chui "
"mou zan uu ying jie liu zhan ya rao zhen dang qi qiao hua hui jiang zhuang xun suo sa chen bei ying kuo jing bo ben fu rui tong jue xi lang liu feng qi wen jun gan su liang qiu ting you mei bang long "
"peng zhuang di juan tu zao ao gu bi di han zi zhi ren bei geng jian huan wan nuo jia tiao ji xiao lv kuan shao cen fen song meng wu li li dou qin ying suo ju ti xie kun zhuo shu chan fan wei jing li "
"bing xia fo chou zhi lai lian jian tuo ling li qi bing lun song qian mian qi qi cai gun chan de fei pai bang bei hun zong chang zao ji li peng yu yu gu gun dong tang gang wang di cuo fan cheng zhan qi "
"yuan yan yu juan yi sen shen chui ling qi zhuo fu ke lai zou zou zhuo guan fen fen chen qing ni wan guo lu hao jie yi chou ju ju cheng cui liang kong zhi zhui ya ju bei jiao zhuo zi bin peng ding chu "
"chang men hua jian gui xi du qian dao gui dian luo zhi juan myeong fu geng peng shan yi tuo san chuan ye fu wei wei duan jia zong jian yi shen po yan yan chuan jian chun yu he zha wo pian bi yao guo xu "
"ruo yang la yan ben hui kui jie kui si feng xie tuo ji jian mu mao chu ku hu lian leng ting nan yu you mei cong xuan xuan yang zhen pian die ji jie ye chu dun yu zou wei mei di ji jie kai qiu ying rou "
"huang lou le quan xiang pin shi gai tan lan wen yu chen lv ju shen chu pi xie jia yi zhan bo nuo mi lang rong gu jin ju ta yao zhen bang sha yuan zi ming su jia yao jie huang gan fei zha qian ma sun "
"yuan xie rong shi zhi cui wen ting liu rong tang que zhai si sheng ta ke xi gu qi gao gao sun pan tao ge chun zhen nou ji shuo gou chui qiang cha qian huai mei chu gang gao zhuo tuo qiao yang zhen jia "
"kan zhi dao long bin zhu sang xi ji lian hui yong qian guo gai gai tuan hua qi shen cui peng you hu jiang hu huan gui nie yi gao kang gui gui cao man jin di zhuang le lang chen cong li xiu qing shuang "
"fan tong guan ze su lei lu liang mi lou chao su ke chu tang biao lu liao zhe zha shu zhang man mo niao yang tiao peng zhu sha xi quan heng jian cong ji yan qiang xue ying er xun zhi qiao zui cong pu shu "
"hua gui zhen zun yue shan xi chun dian fa gan mo wu qiao rao lin liu qiao jian run fan zhan du liao yun shun dun cheng tang meng ju cheng su jue jue tan hui ji nuo xiang tuo ning rui zhu tong zeng fen "
"qiong ran heng qian gu liu lao gao chu xi sheng zi san ji dou jing lu jian chu yuan da qiao jiang tan lin nao yin xi hui shan zui xuan cheng gan ju zui yi qin pu dan lei feng hui dang ji sui bo bo cheng "
"chu zhua hui ji jie jia jing zhai jian qiang dao yi biao song she lin li cha meng yin chou tai mian qi tuan bin huo ji lian mi ning yi gao kan yin ru qing yan qi mi di gui chun ji kui po deng chu ge "
"mian you zhi guang qian lei lei sa lu li cuan lv mie hui ou lv zhi gao du yuan li fei zhu sou lian jiang chu qing zhu lu yan li zhu chen ji e su huai nie yu long lai qiao xian gui ju xiao ling ying jian "
"yin you ying rang nong bo chan lan ju shuang she zui cong quan qu cang jou yu luo li zuan luan dang jue yan lan lan zhu lei li ba nang yu ling guang qian ci huan xin yu yu qian ou xu chao chu qi ai yin "
"jue xi xu he yu kui lang kuan shuo xi ai qi qi xu chuai qin kuan qian kuan kan chuan sha gua yin xin xie yu qian xiao ye ge wu tan jin ou hu ti huan xu pen xi chi xu xi uu lian chu yi e yu chuo huan zhi "
"zheng ci bu wu qi bu bu wai ju qian chi se chi se zhong sui sui li ji yu li gui dai e si jian zhe wen mo yao mo cu yang tian sheng dai shang xu xun shu can jing piao qia qiu su jing yun lian yi bo zhi "
"yan can hun dan ji die zhen yun wen chou bin ti jin shang yin diao jiu kui cuan yi dan du jiang lian bin du jian jian shu ou duan zhu yin sheng yi sa ke ke yao xun dian hui hui gu qiao ji yi kou hui "
"duan yi xiao wu guan mu mei mei ai jie du yu bi bi bi pi pi bi chan mao uu uu bi mao jia zhan sai mu tuo xun er rong xian ju mu hao qiu dou uu tan pei ju duo cui bi san san mao sai shu shu tuo he jian "
"ta san shu mu mao tong rong chang pu lu zhan sao zhan meng lu qu die zhi di min jue mang qi pie nai qi dao xian chuan fen ri nei bin fu shen dong qing qi yin xi hai yang an ya ke qing ya dong dan lv "
"qing yang yun yun shui shui cheng bing yong dang shui le ni qiu fan qiu ding zhi qiu pa ze mian cuan hui diao han cha zhuo chuan wan fan tai xi tuo mang you qi shan chi han qian wu wu xun si ru gong "
"jiang chi wu tu jiu tang zhi zhi qian mi yu wang jing jing rui jun hong tai fu ji bian bian han wen zhong fang xiong jue hu niu qi pen xu xu qin yi wo yun yuan hang yan shen chen dan you dun hu huo qi "
"mu niu mei ta mian wu chong pang bi sha zhi pei pan zhui za gou liu mei ze feng ou li lun cang feng wei hu mo mei shu ju za tuo tuo tuo he zhen ni chi fa fei you tian zhi zhao gu zhan yan si kuang jiong "
"gou xie qiu die jia zhong quan bo hui mi ben ze zhu le ao gu hong gan fa liu si hu ping ci fan di su ning cheng ling pao bo qi si ni ju yue zhu sheng lei xuan xue fu pan min tai yang ji yong guan beng "
"xue long lu dan luo xie po ze jing yin zhou jie shi hui hui zai cheng yan wei hou cun yang lie si ji er xing fu sa zi zhi yin wu xi kao zhu jiang luo uu an dong yi mou lei yi mi quan jin po wei xiao xie "
"hong xu su kuang yao jie ju er zhou ru ping xun xiong zhi huang huan ming huo gui qia pai hu qu liu yi xia jing qian jiang jiao zhen shi zhuo ce peol hui ji liu chan hun hu nong xun jin lie qiu wei zhe "
"jun han bin mang zhuo you xi bo dou huan hong yi pu cheng lan hao lang han li geng fu wu li chun feng yi yu tong lao hai jin xia chong jiong mei sui cheng pei jian shen tu kun ping nie han jing xiao she "
"ren tu yong xiao xian ting e shu yun juan cen ti li shui si lei shui tao du lao lai lian wei wo yun huan di heng run jian zhang se pou guan xing shou shuan ya chuo zhang ye kong wan han tuo dong he wo "
"ju she liang hun ta zhuo dian ji de juan zi xi xiao qi gu guo yan lin chang diao peng hao chang shu qi fang chi lu nao ju tao cong lei zhe peng fei song tian pi dan yu ni yu lu gan mi jing ling lun yin "
"cui qu huai yu nian shen hu chun hu yuan lai hun qing yan qian tian miao zhi yin bo ben yuan wen ruo fei qing yuan ke ji she yuan se lu zi du qi jian mian pi xi yu yuan shen shen rou huan zhu jian nuan "
"yu qiu ting qu du feng zha bo wo wo di wei wen nuo die ce wei he gang yan hong xuan mi ke mao ying yan you hong miao sheng mei zai hun nai gui chi e pai mei lian qi qi mei tian cou wei can tuan mian xu "
"po xu ji pen qian jian hu feng xiang yi yin zhan shi jie zhen huang tan yu bi min shi tu sheng yong ju tong tuan qiu qiu qiu yan tang long huo yuan nan pan you quan zhuang liang chan xian chun nie zi "
"wan shi man ying la kui feng jian xu lou wei gai xia ying po jin gui tang yuan suo yuan lian yao meng zhun cheng ke tai da wa liu gou sao ming zha shi yi lun ma pu wei li zai wu xi wen qiang ze shi shuo "
"ai zhen sou yun xiu yin rong hun su suo ni ta shi ru ai pan xu chu pang weng cang mie ge dian hao huang qi zi di zhi xing fu jie hua ge zi tao teng sui bi jiao hui gun yao gao long zhi yan she man ying "
"chun lv lan luan xiao bin tan yu xiu hu bi biao zhi jiang kou shen shang di mi ao lu hu hu you chan fan yong gun man qing yu piao ji ya chao qi xi ji lu lu long jin guo cong lou zhi gai qiang li yan cao "
"jiao cong chun zhuan ou teng ye xi mi tang mo shang han lian lan wa tai gan feng xuan yi man zi mang kang luo peng shu zhang zhang chong xu huan kuo jian yan shuang liao cui ti yang jiang zong ying hong "
"xin shu guan ying xiao zong kun xu lian zhi wei pie yu jiao po xiang hui jie wu pa ji pan wei su qian qian xi lu xi xun dun huang min run su liao zhen zong yi zhi wan tan tan chao xun kui ye shao tu zhu "
"sa hei bi shan chan chan shu tong pu lin wei se se cheng jiong cheng hua jiao lao che gan cun jing si shu peng han yun liu gong fu hao he xian jian shan xi ao lu lan ning yu lin mian zao dang han ze xie "
"yu li shi xue ling wan zi yong hui can lian dian ye ao huan zhen dan man gan dan yi sui pi ju ta qin ji zhuo lian nong guo jin pen se ji sui hui chu ta song ding se zhu lai bin lian mi shi shu mi ning "
"ying ying meng jin qi bi ji hao ruan cui wo tao yin yin dui ci huo jing lan jun kai pu zhuo wei bin gu qian ying bin kuo fei cang me jian dui luo zan lu li you yang lu si zhi ying du wang hui xie pan "
"shen biao chan mie liu jian pu se cheng gu bin huo xian lu qin han ying rong li jing xiao ying sui wei xie huai xue zhu long lai dui fan hu lai shu ling ying mi ji lian jian ying fen lin yi jian yao "
"chan dai rang jian lan fan shuang yuan jiao feng she lei lan cong qu yong qian fa guan jue yan hao ying sa zan luan yan li mi shan tan dang jiao chan ying hao ba zhu lan lan nang wan luan quan xian yan "
"gan yan yu huo huo mie guang deng hui xiao xiao hui hong ling zao zhuan jiu zha xie chi zhuo zai zai can yang qi zhong fen niu jiong wen pu yi lu chui pi kai pan yan yan feng mu chao liao que kang dun "
"guang xin zhi guang guang wei qiang bian da xia zheng zhu ke zhao fu ba xie xie ling zhuo xuan ju tan pao jiong pao tai tai bing yang tong shan zhu zha dian wei shi lian chi huang zhou hu shuo lan jing "
"jiao xu heng quan lie huan yang xiu xiu xian yin wu zhou yao shi wei tong xue zai kai hong lao xia chong xuan zheng po yan hui guang che hui kao chen fan shao ye hui uu tang jin re lie xi fu jiong che "
"pu jing zhuo ting wan hai peng lang yan xu feng chi rong hu xi shu huo xun kao juan xiao xi yan han zhuang jun di che ji wu uu lv han yan huan men ju tao bei fen lin kun hun tun xi cui wu hong chao fu "
"wo jiao cong feng ping qiong ruo xi qiong xin zhuo yan yan yi jiao yu gang ran pi xiong wang sheng chang shao xiong nian geng qu chen he kui zhong duan xia hui feng lian xuan xing huang jiao jian bi "
"ying zhu wei tuan shan xi xuan nuan chan yan jiong jiong yu mei sha wei ye jin qiong rou mei huan xu zhao wei fan qiu sui yang lie zhu jie sao gua bao hu wen nan shi liang bian gou tui tang chao shan "
"en bo huang xie xi wu xi yun he he xi yun xiong xiong shan qiong yao xun mi qian ying wu rong gong yan qiang liu xi bi biao cong lu jian shou yi lou feng cui yi tong jue zong yun hu yi zhi ao wei liu "
"han ou re jiong man kun shang cuan zeng jian xi xi xi yi xiao chi huang dan ye tan ran yan xun qiao jun deng dun shen jiao fen si liao yu lin tong shao fen fan yan xun lan mei tang yi jiong men jing uu "
"ying yu yi xue lan lie zao can sui xi que cong lian hui zhu xie ling yu yi xie zhao hui da nung bing ru bing xiao xun jin chou tao yao he lan biao rong li mo bao ruo lv lie ao xun kuang shuo liao li lu "
"jue liao yan xi xie long ye can rang yue lan cong jue chong guan ju che mi tang lan zhu lan ling cuan yu zhua zhua pa zheng pao cheng yuan ai wei han jue jue fu ye ba die ye yao zu shuang er pan chuang "
"ke zang die qiang yong qiang pian ban pan chao jian pai du chuang yu zha bian die bang bo chuang you yong du ya cheng niu niu pin le mou ta mu lao ren mang fang mao mu gang wu yan ge bei si jian gu you "
"ke sheng mu di qian quan quan zi te xi mang keng qian wu gu xi li li pou ji gang zhi ben quan chun du ju jia jian feng pian ke ju kao chu xi bei luo jie ma san wei mao dun tong qiao jiang xi li du lie "
"bai piao bao xi chou wei kui chou quan quan ba fan qiu ji chai bao han he zhuang guang ma you kang fei hou ya yin huan zhuang yun kuang niu di kuang zhong mu bei pi ju chi sheng pao xia yi hu ling fei "
"pi ni yao you gou xue ju dan bo ku xian ning huan hen jiao he zhao jie xun shan shi rong shou tong lao du xia shi kuai zheng yu sun yu bi mang xi juan li xia yin jun lang bei zhi yan sha li han xian "
"jing pai fei xiao pi qi ni biao yin lai lie jian qiang kun yan guo zong mi chang ji zhi zheng wei meng cai cu she lie ceon luo hu zong fui wei feng wo yuan xing zhu mao wei chuan xian tuan jia nao xie "
"jia hou bian you you mei cha yao sun bo ming hua yuan sou ma yuan dai yu shi hao qiang yi zhen cang hao man jing jiang mu zhang chan ao ao hao cui fen jue bi bi huang pu lin yu tong xiao liao xi xiao "
"shou dun jiao ge xuan du hui kuai xian xie ta xian xun ning bian huo ru meng lie you guang shou lu ta xian mi rang huan nao luo xian qi jue xuan miao zi shuai lu yu su wang qiu ga ding le ba ji hong di "
"chuan gan jiu yu qi yu yang ma hong wu fu wen jie ya fen men bang yue jue yun jue wan yin mei dan pin wei huan xian qiang ling dai yi gan ping dian fu xuan xi bo ci gou jia shao po ci ke ran sheng shen "
"yi ju jia min shan liu bi zhen zhen jue fa long jin jiao jian li guang xian zhou gong yan xiu yang xu luo su zhu qin yin xun bao er xiang yao xia heng gui chong xu ban pei lao dang ying hun wen e cheng "
"di wu wu cheng jun mei bei ting xian chu han xuan yan qiu xuan lang li xiu fu liu ya xi ling li jin lian suo suo feng wan dian pin zhan cui min yu ju chen lai min sheng wei tian chu zhuo pei cheng hu qi "
"e kun chang qi beng wan lu cong guan yan diao fei lin qin pi pa qiang zhuo qin fa jin qiong du jie hun yu mao mei chun xuan ti xing dai rou min jian wei ruan huan jie chuan jian zhuan yang lian quan xia "
"duan huan ye nao hu ying yu huang rui se liu shi rong suo yao wen wu zhen jin ying ma tao liu tang li lang gui tian cang cuo jue zhao yao ai bin tu chang kun zhuan cong jin yi cui cong ji li jing zao "
"qiu xuan ao lian men zhang yin hua ying wei lu wu deng xiu zeng xun qu dang lin liao jue su huang gui pu jing fan jin liu ji hui jing ai bi can qu zao dang jiao gun tan kuai huan se sui tian chu yu jin "
"fu bin shu wen zui lan xi ji xuan ruan wo gai lei du li zhi rou li zan qiong ti gui sui la long lu li zan lan ying xi xiang qiong guan dao zan huan gua bo die pao gu hu piao ban rang li wa shiwa hong "
"qianwa ban pen fang dan weng ou fenwa milik wa hu ling yi ping ci baiwa juan chang chi liwa dang wa bu zhui ping bian zhou zhen liwa ci ying qi xian lou di ou meng zhuan beng lin zeng wu pi dan weng "
"ying yan gan dai shen tian tian han chang sheng qing shen chan chan rui sheng su shen yong shuai lu pu yong beng feng ning tian you jia shen you dian fu nan dian ping ding hua ding quan zi mang bi bi "
"jiu sun liu chang mu yun fan fu geng tian jie jie quan wei fu tian mu tap pan jiang wa fu nan liu ben zhen chu mu mu ji tian gai bi da zhi lue qi lue fan yi fan hua she she mu jun yi liu she die chou "
"hua dang zhui qi wan jiang cheng chang tuan lei ji cha liu die tuan lin jiang jiang chou pi die die pi jie dan shu shu zhi yi ne nai ding bi jie liao gang ge jiu zhou xia shan xu nue li yang chen you "
"ba jie jue qi ya cui bi yi li zong chuang feng zhu pao pi gan ke ci xue zhi dan zhen bian zhi teng ju ji fei ju shan jia xuan zha bing ni zheng yong jing quan chong tong yi jie you hui shi yang chi "
"zhi hen ya mei dou jing xiao tong tu mang pi xiao suan pu li zhi cuo duo wu sha lao shou huan xian yi peng zhang guan tan fei ma ma chi ji dian an chi bi bi min gu dui ke wei yu cui ya zhu cu dan shen "
"zhong chi yu hou feng la yang chen tu yu guo wen huan ku xia yin yi lou sao jue chi xi guan yi wen ji chuang ban hui liu cuo shou nue dian da bie tan zhang biao shen cu luo yi zong lu zhang ji sou se "
"que diao lou lou mo qin yin ying huang fu liao long jiao liu lao xian fei dan yin he ai ban xian guan gui nong yu wei yi yong pi lei li shu dan lin dian lin lai bie ji chi yang xuan jie zheng me li huo "
"lai ji dian xuan ying yin qu yong tan dian luo luan luan bo uu gui ba fa deng fa bai bai qie bi zao zao mao de ba jie huang gui ci ling gao mo ji jiao peng gao ai e hao han bi wan chou qian xi ai po "
"hao huang hao ze cui hao xiao ye pan hao jiao ai xing huang li piao he jiao pi gan pao zhou jun qiu cun que zha gu jun jun zhou zha uu zhan du min qi ying yu bei zhao zhong pen he ying he yi bo wan he "
"ang zhan yan jian he yu kui fan gai dao pan fu qiu sheng dao lu zhan meng li jin xu jian pan guan an lu xu chou dang an gu li mu ding gan xu mang mang zhi qi yuan xian xiang dun xin xi pan feng dun min "
"ming sheng shi yun mian pan fang miao dan mei mao kan xian kou shi ying zheng ao shen huo da zhen kuang ju shen yi sheng mei mie zhu zhen zhen mian shi yuan die ni zi zi chao zha xuan bing pan long sui "
"tong mi zhi di ne ming xun chi kuang juan mou zhen tiao yang yan mo zhong mo zhuo zheng mei juan shao han huan ti cheng cuo juan e man xian xi kun lai jian shan tian huan wan leng shi qiong li ya jing "
"zheng li lai sui juan shui hui du pi bi mu hun ni lu gao jie cai zhou yu hun ma xia xing hui gun zai chun jian mei du hou xuan tian kui gao rui mao xu fa wo miao chou kui mi weng kou dang chen ke sou "
"xia huan mo ming man fen ze zhang yi diao kou mo shun cong lou chi man piao cheng gui meng huan shun pie xi qiao pu zhu deng shen shun liao che jian kan ye xu tong wu lin kui jian ye ai hui zhan jian gu "
"zhao qu wei chou sao ning xun yao huo meng mian pin mian lei kuang jue xuan mian huo lu meng long guan man li chu tang kan zhu mao jin jin yu shuo zhuo jue shi yi shen zhi hou shen ying ju zhou jiao cuo "
"duan ai jiao zeng yue ba shi ding qi ji zi gan wu da ku gang xi fan kuang dang ma sha dan jue li fu min e hua kang zhi qi kan jie fen e ya pi zhe yan sui zhuan che dun wa yan jin feng fa mo zuo zu yu ke "
"tuo tuo di zhai zhen e fei mu zhu li bian nu ping peng ling pao le po bo po shen za ai li long tong yong li kuang chu keng quan zhu guang gui e nao qia lu wei ai ge ken xing yan dong peng xi lao hong "
"shuo xia qiao qing ai qiao ji qing xiao ku chan lang hong yu xiao xia bang long yong che che wo liu ying mang que yan sha kun gu ceok hua lu cen jian nue song zhuo keng peng yan chui kong cheng qi cong "
"qing lin jun pan ding min diao zhan he lu ai sui xi leng bei yin dui wu qi lun wan dian gang bei qi chen ruan yan die ding zhou tuo jie ying bian ke bi wei shuo zhen duan xia dang ti nao peng jian di "
"tan cha tian qi dun feng xuan que que ma gong nian xie e ci liu ti tang bang hua pi kui sang lei cuo tian xia qi lian pan ai yun chui zhe ke la pak yao gun zhuan chan qi ao peng liu lu kan chuang ca yin "
"lei piao qi mo qi cui zong qing chuo lun ji shan lao qu zeng deng jian xi lin ding dian huang pan ji ao di li jian jiao xi zhang qiao dun jian yu zhui he huo ze lei jie chu ye que dang yi jiang pi pi yu "
"pin qi ai ke jian yu ruan meng pao ci bo yang ma ca xian kuang lei lei zhi li li fan que pao ying li long long mo bo shuang guan lan ca yan shi shi li reng she yue si qi ta ma xie yao xian zhi qi zhi "
"fang dui zhong uu yi shi you zhi tiao fu fu mi jie zhi suan mei zuo qu hu zhu shen sui ci chai mi lv yu xiang wu tiao piao zhu gui xia zhi ji gao zhen gao shui jin shen gai kun di dao huo tao qi gu guan "
"zui ling lu bing jin dao zhi lu chan bi chu hui you xi yin zi huo zhen fu yuan xu xian yang zhi yi mei si di bei zhuo zhen yong ji gao tang si ma ta fu xuan qi yu xi ji si chan dan gui sui li nong mi dao "
"li rang yue ti zan lei rou yu yu li xie qin he tu xiu si ren tu zi cha gan zhi xian bing nian qiu qiu zhong fen hao yun ke miao zhi jing bi zhi yu mi ku ban pi ni li you zu pi bo ling mo cheng nian qin "
"yang zuo zhi zhi shu ju zi kuo ji cheng tong zhi kuo he yin zi zhi jie ren du chi zhu hui nong bu xi gao lang fu xun shui lv kun gan jing ti cheng tu shao shui ya lun lu gu zuo ren zhun bang bai qi zhi "
"zhi kun ling peng ke bing chou zui yu su lue uu yi qie bian ji fu bi nuo jie zhong zong xu cheng dao wen xian zi yu ji xu zhen zhi dao jia ji gao gao gu rong sui rong ji kang mu cen mi zhi ji lu su ji "
"ying wen qiu se kweok yi huang qie ji sui rao pu jiao bo tong zui lu sui nong se hui rang nuo yu pin ji tui wen cheng huo kuang lv biao se rang jue li zan xue wa jiu qiong xi kong kong yu shen jing yao "
"chuan tun tu lao qie zhai yao bian bao yao bing wa zhu liao qiao diao wu wa yao zhi chuang yao tiao jiao chuang jiong xiao cheng kou cuan wo dan ku ke zhuo huo su guan kui dou zhuo yin wo wa ya yu lou "
"qiong yao yao tiao chao yu tian diao lou liao xi wu kui chuang ke kuan kuan long cheng cui liao zao cuan qiao qiong dou zao long qie li chu shi fu qian chu hong qi hao sheng fen shu miao qu zhan zhu ling "
"long bing jing jing zhang bai si jun hong tong song zhen diao yi shu jing qu jie ping duan li zhuan ceng deng cun wai jing kan jing zhu zhu le peng yu chi gan mang zhu wan du ji jiao ba suan ji qin zhao "
"sun ya rui yuan wen hang xiao cen bi bi jian yi dong shan sheng xia di zhu na chi gu li qie min bao tiao si fu ce ben ba da zi di ling zuo nu fu gou fan jia gan fan shi mao po shi jian qiong long min bian "
"luo gui qu chi yin yao xian bi qiong kuo deng jiao jin quan sun ru fa kuang zhu tong ji da hang ce zhong kou lai bi shai dang zheng ce fu yun tu pa li lang ju guan jian han tong xia zhi cheng suan shi zhu "
"zuo xiao shao ting jia yan gao kuai gan chou kuang gang yun o qian xiao jian pou lai bei pai bi bi ge tai guai yu jian dao gu hu zheng jing sha zhou lu bo ji lin suan jun fu zha gu kong qian quan jun chui "
"guan wan ce zu bo zhai qie tuo luo dan xiao ruo jian xuan bian sun xiang xian ping zhen sheng hu shi zhu yue chun lv wu dong xiao ji jie huang xing mei fan chuan zhuan pian feng zhu hong qie hou qiu miao "
"qian gu kui shi lou yun he tang yue chou gao fei ruo zheng gou nie qian xiao cuan gong pang du li bi zhuo chu shi chi zhu cang long lan jian bu li hui bi zhu cong yan peng zan zuan pi piao dou yu mie zhuan "
"zhai shai guo yi hu chan kou cu ping zao ji gui su lou ce lu nian suo cuan diao suo le duan liang xiao bo mie si dang liao dan dian fu jian min kui dai jiao deng huang zhuan lao zan xiao lu shi zan qi pai qi "
"pi gan ju lu lu yan bo dang sai ke gou qian lian bu zhou lai shi lan kui yu yue hao zhen tai ti mi chou jie yi qi teng zhuan zhou fan sou zhou qian zhuo teng lu lu jian tuo ying yu lai long qie lian lan qian "
"yue zhong ju lian bian duan zuan li shi luo ying yue zhuo yu mi di fan shen zhe shen nv he lei xian zi ni cun zhang qian zhai pi ban wu sha kang rou fen bi cui yin zhe mi tai hu ba li gan ju po mo cu nian zhou "
"chi su diao li xi su hong tong ci ce yue zhou lin zhuang bai lao fen er qu he liang xian fu liang can jing li yue lu ju qi cui bai zhang lin zong jing guo hua shen shen tang bian rou mian hou xu zong hu jian zan "
"ci li xie fu nuo bei gu xiu gao tang qiu jia cao zhuang tang mi shen fen zao kang jiang mo san san nuo xi liang jiang kuai bo huan shu ji xian nuo tuan nie li zuo di nie tiao lan si si jiu xi gong zheng jiu you "
"ji cha zhou xun yue hong yu he wan ren wen wen qiu na zi tou niu fou jie shu chun pi zhen sha hong zhi ji fen yun ren dan jin su fang suo cui jiu zha ba jin fu zhi qi zi chou hong zha lei xi fu xie shen bo zhu "
"qu ling zhu shao gan yang fu tuo zhen dai chu shi zhong xuan zu jiong ban qu mo shu zui kuang jing ren hang yi jie zhu chou gua bai jue kuang hu ci geng geng tao jie ku jiao quan ai luo xuan bing xian fu gei tong "
"rong tiao yin lei xie juan xu hai die tong si jiang xiang hui jue zhi jian juan chi wan zhen lv cheng qiu shu bang tong xiao wan qin geng xiu ti xiu xie hong xi fu ting sui dui kun fu jing hu zhi xian jiong feng ji "
"xu ren zong lin duo li lv liang chou quan shao qi qi zhun qi wan qing xian shou wei qi tao wan gang wang beng zhui cai guo cui guan liu qi zhan bi chuo ling mian qi qie tan zong hun zou xi zi xing liang jin fei rui "
"hun yu zong fan lv xu ying shang qi xu xiang jian ke xian ruan mian qi duan zhong di min miao yuan xie bao si qiu bian huan geng cong mian wei fu wei xu gou miao xie lian zong bian yun yin ti gua zhi yun cheng chan "
"dai xia yuan zong xu sheng wei geng seon ying jin yi zhui ni bang hu pan zhou jian cuo quan shuang yun xia shuai xi rong tao fu yun zhen gao ru hu zai teng xian su zhen zong tao huang cai bi feng cu li su yan xi zong "
"lei zhuan qian man zhi lv mo piao lian mi xuan zong ji shan cui fan lv beng yi sao miu yao qiang sheng xian xi sha xiu ran xuan sui qiao zeng zuo zhi shan san lin yu fan liao chuo zun jian rao chan rui xiu hui hua zuan "
"xi qiang yun da sheng hui xi se jian jiang huan sao cong xie jiao bi tan yi nong sui yi sha ru ji bin qian lan pu xun zuan qi peng li mo lei xie zuan kuang you xu lei xian chan jiao lu chan ying cai xiang xian zui zuan "
"luo li du lan lei lian si jiu yu hong zhou qian he yue ji wan kuang ji ren wei yun hong chun pi sha gang na ren zong guan fen zhi wen fang zhu zhen niu shu xian gan yi fu lian zu shen xi zhi zhong zhou ban fu chu shao yi "
"jing dai bang rong jie ku rao die hang hui gei xuan jiang luo jue jiao tong geng shao juan xiu xi sui tao ji ti ji xu ling ying xu qi fei chuo shang gun sheng wei mian shou beng chou tao liu quan zong zhan wan lv zhui zi "
"ke xiang jian mian lan ti miao qi yun hui si duo duan bian xian gou zhui huan di lv bian min yuan jin fu ru zhen feng shuai gao chan li yi jian bin piao man lei ying su miu sao xie liao shan ceng jiang qian sao huan jiao "
"zuan fou xie gang fou que fou qi bo ping xiang zhao gang ying ying qing xia guan zun tan cang qi weng ying lei tan lu guan wang wang wang wang han ra luo fu shen fa gu zhu ju mao gu min gang ba gua ti juan fu shen yan zhao "
"zui gua zhuo yu zhi an fa lan shu si pi ma liu ba fa li chao wei bi ji zeng chong liu ji juan mi zhao luo pi ji ji luan yang mi qiang da mei yang you you fen ba gao yang gu qiang yang gao ling yi zhu di xiu qiang yi xian "
"rong qun qun qiang huan suo xian yi yang kong xian yu geng jie tang yuan xi fan shan fen shan lian lei geng nou qiang chan yu hong yi chong weng fen hong chi chi cui fu xia ben yi la yi pi ling lu zhi qu xi xie xiang xi xi "
"ke qiao hui hui shu sha hong jiang zhai cui fei zhou sha chi zhu jian xuan chi pian zong wan hui hou he hao han ao piao yi lian qu ao lin pen qiao ao fan yi hui xuan dao yao lao uu kao mao zhe qi gou gou gou die die er shua "
"ruan er nai zhuan lei ting zi geng chao hao yun pa pi yi si chu jia ju huo chu lao lun jie tang ou lou nou jiang pang ze lou ji lao huo you mo huai er yi ding ye da song qin yun chi dan dan hong geng zhi uu nie dan zhen che "
"ling zheng you tui liao long zhi ning tiao er ya tie guo sei lian hao sheng lie pin jing ju bi zhi guo wen xu ping cong ding uu ting ju cong kui lian kui cong lian weng kui lian lian cong ao sheng song ting kui nie zhi dan ning "
"qie jian ting ting long yu nie zhao si su si su si zhao zhao rou yi le ji qiu ken cao ge di huan huang chi ren xiao ru zhou yuan du gang rong gan cha wo chang gu zhi qin fu fei fen pei feng jian fang zhun you na ang ken ran gong "
"yu wen yao qi pi qian xi xi fei ken jing tai shen zhong zhang xie shen wei zhou die dan fei ba bo qu tian bei gua tai zi ku shi ni ping ci fu pang zhen xian zuo pei jia sheng zhi bao mu qu hu ke chi yin xu yang long dong ka lu "
"jing nu yan pang kua yi guang hai ge dong zhi jiao xiong xiong er an heng pian neng zi gui cheng tiao zhi cui mei xie cui xie mai mai ji xie nin kuai sa zang qi nao mi nong luan wan bo wen huan xiu jiao jing rou heng cuo luan shan "
"ting mei chun shen jia te zui cu xiu xin tuo pao cheng nei pu dou tuo niao nao pi gu luo li lian zhang cui jie liang shui pi biao lun pian guo juan chui dan tian nei jing nai la ye yan ren shen zhui fu fu ju fei qiang wan dong bi "
"guo zong ding wo mei ruan zhuan chi cou luo ou di an xing nao yu shuan nan yun zhong rou e sai dun yao jian wei jiao yu jia duan bi chang fu xian ni mian wa teng tui bang qian lv wa shou tang su zhui ge yi bo liao ji pi xie gao lv "
"bin ou chang lu guo pang chuai piao jiang fu tang mo xi zhuan lu jiao ying lou zhi xue cen lin tong peng ni chuai liao cui kui xiao teng pan zhi jiao shan wu cui run xiang sui fen ying shan zhua dan kuai nong tun lian bei yong ju "
"chu yi juan ge lian sao tun gu qi cui bin xun ru wo zang xian biao xing kun la yan lu huo za luo qu zang luan luan zan chen xian wo jiong zang lin jiong zi jiao nie chou ji hao chou bian nie zhi zhi ge jian zhi zhi xiu tai zhen jiu "
"xian yu cha yao yu chuang xi xi jiu yu yu xing ju jiu xin she she she jiu shi ran shu shi tian tan pu pu guan hua tian chuan shun xia wu zhou dao xiang shan yi fan pa tai fan ban chuan hang fang ban bi lu zhong jian cang ling zhou ze "
"duo bo xian ge chuan xia lu hong pang xi kua fu zao feng li shao yu lang ting uu wei bo meng nian ju huang shou zong bian mo die dou bang cha yi sou cang cao lou dai xue tiao tong deng dang qiang lu yi "
"ji jian huo meng qi lu lu chan shuang gen liang jian jian se yan fu ping yan yan cao cao yi le ding qiu ai nai tiao jiao jie peng wan yi cha mian mi gan qian yu xu shao xiong du xia qi mang zi hui sui "
"zhi xiang pi fu chun wei wu zhi qi shan wen qian ren fu kou jie lu xu ji qin chi yuan fen ba rui xin ji hua hua fang wu jue ji zhi yun qin ao chu mao ya fei reng hang cong yin you bian yi qie wei li pi "
"e xian chang cang zhu su ti yuan ran ling tai tiao di miao qing li yong he mu bei bao gou min yi yi ju pie ruo ku ning ni pa bing shan xiu yao xian ben hong ying zha dong ju die nie gan hu ping mei fu "
"sheng gua bi wei fu zhu mao fan qie mao mao ba ci mo zi zhi chi ji jing long cong niao uu xue ying qiong ge ming li rong yin gen qian chai chen yu xiu zi lie wu duo gui ci chong ci hou guang mang cha "
"jiao niao fu yu zhu zi jiang hui yin cha fa rong ru chong mang tong zhong qian zhu xun huan fu quan gai da jing xing chuan cao jing er an qiao chi ren jian yi huang ping li qian lao shu zhuang da jia "
"rao bi ce qiao hui ji dang yu rong hun xing luo ying xun jin sun yin mai hong zhou yao du wei li dou fu ren yin he bi bu yun di tu sui sui cheng chen wu bie xi geng li fu zhu mo li zhuang zuo tuo qiu "
"sha suo chen peng ju mei qing xing jing che xin jun yan ting you cuo guan han you cuo jia wang you niu xiao xian liang fu e mo mian jie nan mu kan lai lian shi wo tu xian huo you ying ying neus chun "
"mang mang ci wan jing di qu dong guan chu gu la lu ju wei jun ren kun he pu zi gao guo fu lun chang chou song chui zhan men cai ba li tu bo han bao qin juan xi qin di jie pu dang jin zhao zhi geng hua "
"gu ling fei jin yan wang beng zhou yan ju jian lin tan shu tian dao hu ji he cui tao chun pi chang huan fei lai qi meng ping wei dan sha zhui yan yi shao qi guan ce nai zhen ze jiu tie luo bi yi meng "
"be pao ding ying ying ying xiao sa qiu ke xiang wan yu yu fu lian xuan xuan nan ce wo chun xiao yu pian mao an e luo ying huo kuo jiang mian zuo zuo zu bao rou xi ye yan qu jian fu lv jing pen feng "
"hong hong hou yan tu zhe zi xiang shen ge qia jing mi huang shen pu gai dong zhou jian wei bo wei pa ji hu zang xia duan yao jun cong quan wei zhen kui ting hun xi shi qi lan zong yao yuan mei yun shu "
"di zhuan guan ran xue chan kai kui uu jiang lou wei pai yong sou yin shi chun shi yun zhen lang na meng li que suan yuan li ju xi bang chu shu tu liu huo dian qian zu po cuo yuan chu yu kuai pan pu pu "
"na shuo xi fen yun zheng jian ji ruo cang en mi hao sun zhen ming sou xu liu xi gu lang rong weng gai cuo shi tang luo ru suo xuan bei yao gui bi zong gun zuo tiao ce pei lan uu ji li shen lang yu ling "
"ying mo tiao xiu mao tong zhu peng an lian cong xi ping qiu jin chun jie wei tui cao yu yi zi liao bi lu xu bu zhang lei qiang man yan ling ji piao gun han di su lu she shang di mie hun man bo dai cuo "
"zhe shen xuan wei hu ao mi lou cu zhong cai po jiang mi cong niao hui juan yin jian yan shu yin guo chen hu sha kou qian ma cang ze qiang dou lian lin kou ai bi li wei ji xun sheng fan meng ou chan dian "
"xun jiao rui rui lei yu qiao zhu hua jian mai yun bao you qu lu yao hui e ti fei jue zui fa ru fen kui shun rui ya xu fu jue dang wu dong si xiao xi long yun shao ji jian yun sun ling yu xia yong ji "
"hong si nong lei xuan yun yu xi hao bo hao ai wei hui hui ji zi xiang luan mie yi leng jiang can shen qiang lian ke yuan da zhi tang xue bi zhan sun lian fan ding xie gu xie shu jian kao hong sa xin xun "
"yao bai sou shu xun dui pin yuan ning chou mai ru piao tai ji zao chen zhen er ni ying gao cong hao qi fa jian yu kui jie bian di mi lan jin cang mo qiong qie xian uu ou xian su lv yi xu xie li yi la "
"lei jiao di zhi bei teng yao mo huan biao fan sou tan tui qiong qiao wei liu hui ou kao yun bao li zhu zhu ai lin zao xuan qin lai huo ze e rui rui ji heng lu su tui mang yun ping yu xun ji jiong xuan "
"mo qiu su jiong feng nie bo xiang yi xian yu ju lian lian yin qiang ying long tou hua yue ling ju yao fan mei lan kui lan ji dang man lei lei hui feng zhi wei kui zhan huai li ji mi lei huai luo ji kui "
"lu jian sal teng lei quan xiao yi luan men bie hu hu lu nve lv ti xiao qian chu hu xu cuo fu xu xu lu hu yu hao jiao ju guo bao yan zhan zhan kui bin xi shu hui qiu diao ji qiu ding shi uu jue zhe ye yu "
"han zi hong hui meng ge sui xia chai shi yi ma xiang fang e ba chi qian wen wen rui bang pi yue yue jun qi tong yin zhi can yuan jue you qin qi zhong ya ci mu wang fen fen hang gong zao fu ran jie fu "
"chi dou bao xian ni dai qiu you zha ping chi you ke han ju li fu ran zha gou pi pi xian zhu diao bie bing gu zhan qu she tie ling gu dan gu ying li cheng qu mou ge ci hui hui mang fu yang wa lie zhu yi "
"xian kuo jiao li xu ping jie ge she yi wang mo gong qie gui qiong zhi man lao zhe jia nao si qi xing jie qiu xiao yong jia tui che bei e han shu xuan feng shen shen pu xian zhe wu fu li liang bi yu xuan "
"you jie dan dan ting dian tui hui wo zhi song fei ju mi qi qi yu jun la meng qiang xi xi lun li die tiao tao kun han han yu bang fei pi wei tun yi yuan suo quan qian rui ni qing wei liang guo wan dong "
"e ban zhuo wang can mi ying guo chan uu la ke ji xie ting mao xu mian yu jie shi xuan huang yan bian rou wei fu yuan mei wei fu ruan xie you qiu mao xia ying shi zhong tang zhu zong ti fu yuan kui meng "
"la du hu qiu die li wo yun yu nan lou chun rong ying jiang tui lang pang si ci ci xi yuan weng lian sou pan rong rong ji wu xiu han qin yi pi hua tang yi du neng xia hu gui ma ming yi wen ying teng "
"zhong cang so qi man tiao shang zhe cao chi dai ao lu wei zhi tang chen piao ju pi yu jian luo lou qin zhong yin jiang shuai wen xiao man zhe zhe mo ma yu liu mao xi cong li man xiao chang zhang mang "
"xiang mo zui si qiu te zhi peng peng qiao qu bie liao fan gui xi ji zhuan huang ben lao jue jue hui xun chan jiao shan rao xiao wu chong xun si chu cheng dang li xie shan yi jing da chan ji ji xiang she "
"guo qin ying chai li zei xuan lian shu ze xie mang xie qi rong jian meng hao ru huo zhuo jie bin he mie fan lei jie la mian li chun li qiu nie lu du xiao chu long li long pang ye pi rang gu juan ying "
"shu xi can qu quan du can man jue jie shu zhuo xie huang nv fou nv xin zhong mai er ka mie xi xing yan kan yuan qu ling xuan shu xian tong long jie xian ya hu wei dao chong wei dao zhun heng qu yi yi bu "
"gan yu biao cha yi shan chen fu gun fen shuai jie na zhong dan yi zhong zhong jie zhi xie ran zhi ren qin jin jun yuan mei chai ao niao yi ran jia tuo ling dai pao pao yao zuo bi shao tan ju ke xue xiu "
"zhen tuo pa bo di wa fu gun zhi zhi ran pan yi mao tuo jue gou xuan chan qu bei yu xi mi bo uu fu chi chi ku ren jiang qia zun bo jie er ge ru zhu gui yin cai lie ka xing zhuang dang sed kun ken niao "
"shu xie kun cheng li juan shen bao jie yi yu zhen liu qiu qun ji yi bu zhuang shui sha qun li lian lian ku jian bao tan bi kun tao yuan ling chi chang chou duo biao liang shang pei pei fei yuan luo guo "
"yan du xi zhi ju qi qi guo gua ken qi ti ti fu zhong xie bian die kun tuan xiu xiu he yuan bao bao fu yu tuan yan yi bei chu lv pao dan yun ta gou da huai rong yuan ru nai jiong suo pan tun chi sang "
"niao ying jie qian huai ku lian lan li zhe shi lv nie die xie xian wei biao cao ji qiang sen bao xiang bi pu jian zhuan jian cuo ji chan za bo bo xiang xun bie rao man lan ao ze hui cao sui nong chan "
"lian bi jin dang shu tan bi lan pu ru zhi tae shu wa shi bai xie bo chen lai long xi xian lan zhe dai ju zan shi jian pan yi lan ya xi xi yao ban qin fu fiao fu ba he ji ji jian guan bian yan gui jiao "
"pian mao mi mi pie shi si chan zhen jue mi tiao lian yao zhi jun xi shan wei xi tian yu lan e du qin pang ji ming ying gou qu zhan jin guan deng jian luan qu jian wei jue qu luo lan shen ji guan jian "
"guan yan gui mi shi chan lan jue ji xi ji tian yu gou jin qu jiao qiu jin chu jue zhi chao ji gu dan zui di shang xie quan ge shi jie gui gong chu xie hun qiu xing su ni ji lu zhi da bi xing hu shang "
"gong zhi xue chu xi yi li jue xi yan xi yan yan ding fu qiu qiu jiao heng ji fan xun diao hong cha tao xu ji yi ren xun yin shan qi tuo ji xun yin e fen ya yao song shen jin xin jue xiao ne chen you zhi "
"xiong fang xin chao she yan sa zhun xu yi yi su chi he shen he xu zhen zhu zheng gou zi zi zhan gu fu jian die ling di yang li nu pan zhou gan yi ju yao zha tuo yi qu zhao ping bi xiong chu ba da zu tao "
"zhu ci zhe yong xu xun yi huang he shi cha xiao shi hen cha gou gui quan hui jie hua gai xiang wei shen chou tong mi zhan ming luo hui yan xiong gua er bing tiao yi lei zhu kuang kua wu yu teng ji zhi "
"ren cu lang e kuang yi shi ting dan bei chan you keng qiao qin shua an yu xiao cheng jie xian wu wu gao song bu hui jing shuo zhen shuo du hua chang shui jie ke qu cong xiao sui wang xian fei lai ta yi "
"ni yin diao bei zhuo chan chen zhun ji qi tan zhui wei ju qing dong zheng cuo zhou qian zhuo liang jian chu hao lun nie biao hua bian yu die xu pian shi xuan shi hun gua e zhong di xie fu pu ting jian "
"qi yu zi zhuan xi hui yin an xian nan chen feng zhu yang yan huang xuan ge nuo qi mou ye wei xing teng zhou shan jian pao kui huang huo ge ying mi sou mi xi qiang zhen xue ti su bang chi qian shi jiang "
"yuan xie xiao tao yao yao zhi xu biao cong qing li mo mo shang zhe miu jian ze zu lian lou can ou gun xi shu ao ao jin zhe yi hu jiang man chao han hua chan xu zeng se xi zha dui zheng xiao lan e ying "
"jue ji zun qiao bo hui zhuan mo jian zha shi qiao tan zen pu sheng xuan zao tan dang sui xian ji jiao jing lian nang yi ai zhan pi hui hui yi yi shan rang nou qian dui ta hu chou hao yi ying jian yu "
"jian hui du zhe xuan zan lei shen wei chan li yi bian zhe yan e chou wei chou yao chan rang yin lan chan xie nie huan zan yi dang zhan yan du yan ji ding fu ren ji jie hong tao rang shan qi tuo xun yi "
"xun ji ren jiang hui ou ju ya ne xu e lun xiong song feng she fang jue zheng gu he ping zu shi xiong zha su zhen di chou ci chu zhao bi yi yi kuang lei shi gua shi jie hui cheng zhu shen hua dan gou "
"quan gui xun yi zheng gai xiang cha hun xu chou jie wu yu qiao wu gao you hui kuang shuo song ei qing zhu zhou nuo du zhuo fei ke wei yu shui mie diao chan liang zhun sui tan shen yi mou chen die huang "
"jian xie nue ye wei e yu xuan chan zi an yan di mi pian xu mo dang su xie yao bang shi qian mi jin man zhe jian miu tan jian qiao lan pu jue yan qian zhan chan gu qian hong xia ji hong han hong xi xi "
"huo liao han du long dou jiang qi chi feng deng wan bi shu xian feng zhi zhi yan yan shi chu hui tun yi tun yi yan ba hou e chu xiang huan jian ken gai ju fu xi bin hao yu zhu jia fen xi hu wen huan bin "
"di zong fen yi zhi bao chai an pi na pi gou duo you diao mo si xiu huan ken he he mo an mao li ni bi yu jia tuan mao pi xi yi lou mo chu tan huan jue bei zhen yuan fu cai gong dai yi hang wan pin huo "
"fan tan guan ze zhi er zhu shi bi zi er gui pian bian mai dai sheng kuang fei tie yi chi mao he ben lu lin hui gai pian zi jia xu zei jiao gai zang jian ying xun zhen she bin bin qiu she chuan zang zhou "
"lai zan ci chen shang tian pei geng xian mai jian sui fu tan cong cong zhi ji zhang du jin xiong chun yun bao zai lai feng cang ji sheng yi zhuan fu gou sai ze liao yi bai chen wan zhi zhui biao bin "
"zeng dan zan yan pu shan wan ying jin gan xian zang bi du shu yan uu xuan long gan zang bei zhen fu yuan gong cai ze xian bai zhang huo zhi fan tan pin bian gou zhu guan er jian ben shi tie gui kuang "
"dai mao fei he yi zei zhi jia hui zi lin lu zang zi gai jin qiu zhen lai she fu du ji shu shang ci bi zhou geng pei dan lai feng zhui fu zhuan sai ze yan zan bin zeng shan ying gan chi xi she nan xiong "
"xi cheng he cheng zhe xia tang zou zou li jiu fu zhao gan qi shan qiong qin xian ci jue qin di ci chen chen die ju chao di xi zhan jue yue qu jie chi chu gua chi ci tiao duo lie gan suo cu xi zhao su "
"yin ju jian que tang chuo cui lu qu dang qiu zi ti qu chi huang qiao qiao jiao zao yao er zan zan zu pa bao wu ke dun jue fu chen yan fang zhi qi yue ba ji yue qiang chi tai yi chen ling mei ba die ku "
"tuo jia ci pao qia zhu ju zhan zhi fu pan ju shan po ni ju li gen yi ji duo xian jiao duo zhu quan kua zhuai gui qiong kui xiang chi lu pian zhi jia tiao cai jian da qiao bi xian duo ji qu ji shu duo cu "
"jing nie xiao bu xue cun mu shu liang yong jiao chou qiao meo ta jian ji wo cu chuo jie ji nie ju nie lun lu leng huai ju chi wan juan ti pou cu qie qi cu zong cai zong peng zhi zheng dian zhi yu duo "
"dun chun yong zhong chi zha chen chuai jian tuo tang ju fu cu die pian rou nuo ti cha tui jian dao cuo xi ta qiang nian dian di ji nie man liu zan bi chong lu liao cu tang dai su xi kui ji zhi qiang di "
"man zong lian beng zao ran bie tui ju deng ceng xian fan chu zhong dun bo jiu cu jue jue lin ta qiao qiao pu liao dun cuan guan zao da bi bi zhuo ju chuo qiao dun chou ji wu yue nian lin lie zhi li zhi "
"chan chu duan wei long lin xian wei zuan lan xie rang xie nie ta qu ji cuan zuan xi kui jue lin shen gong dan fen qu ti duo duo gong lang ren luo ai ji ju tang kong uu yan mei kang qu lou lao duo zhi "
"yan ti dao ying yu che ga gui jun wei yue xin dai xuan fan ren shan kuang shu tun qi tai e na qi mao ruan kuang qian zhuan hong hu gou kuang di ling dai ao zhen fan kuang yang peng bei gu gu pao zhu fu "
"e ba zhou zhi yao ke yi qing shi ping er gong ju jiao guang he kai quan zhou zai zhi she liang yu shao you wan qun zhe wan fu qing zhou ni ling zhe zhan liang zi hui wang chuo guo kan yi peng qian gun "
"nian ping guan bei lun pai liang ruan rou ji yang xian chuan cou chun ge you hong shu fu zi fu wen fan nian yu yun tao gu zhen xia yuan lu jiao chao zhuan wei xuan xue zhe jiao zhan bu liao fen fan lin "
"ge se kan huan yi ji zhui er yu jian hong lei pei li li lu lin che ga gui xuan dai ren zhuan e lun ruan hong gu ke lu zhou zhi yi hu zhen li yao qing shi zai zhi jiao zhou quan he jiao zhe fu liang nian "
"bei hui gun wang liang chuo zi cou fu ji wen shu pei yuan xia nian lu zhe lin xin gu ci ci pi zui bian la la ci xue ban ban bian bian uu bian ban ci bian bian chen ru nong nong zhen chuo zou yi reng "
"bian bian shi ru liao da chan gan qian yu yu qi xun yi guo mai qi bi kuang tu zhun ying da yun jin hang ya fan wu da e huan zhe zhong jin yuan wei lian chi che ni tiao chi yi jiong jia chen dai er di po "
"zhu die ze tao shu tuo qu jing hui dong you mi beng ji nai yi jie zhui lie xun tui song shi tao feng hou ni dun jiong xuan xun bu you xiao qiu tou zhu qiu di di tu jing ti dou yi zhe tong guang wu shi "
"cheng su zao qun feng lian suo hui li gu lai ben cuo zhu beng huan dai lu you zhou jin yu chuo kui wei ti yi da yuan luo bi nuo yu dang sui dun sui yan chuan chi ti yu shi zhen you yun e bian guo e xia "
"huang qiu dao da wei nan yi gou yao chou liu xun ta di chi yuan su ta qian ma yao guan zhang ao shi ca chi su zao zhe dun shi lou chi cuo lin zun rao qian xuan yu yi e liao ju shi bi yao mai xie sui "
"huan zhan teng er miao bian bian la li yuan yao luo li yi ting deng qi yong shan han yu mang ru qiong wan kuang fu hang bin fang xing na xin shen bang yuan cun huo xie bang wu ju you han tai qiu bi pi "
"bing shao bei wa di zou ye lin kuang gui zhu shi ku yu gai he xi zhi ji xun hou xing jiao xi gui nuo lang jia kuai zheng lang yun yan cheng dou xi lv fu wu fu gao hao lang jia geng jun ying bo xi ju li "
"yun bu xiao qi pi qing guo zhou tan zou ping lai ni chen you bu xiang dan ju yong qiao yi dou yan mei ruo bei e shu juan yu yun hou kui xiang xiang sou tang ming xi ru chu jin zou ye wu xiang yun hao "
"yong bi mao chao lu liao yin zhuan hu qiao yan zhang man qiao xu deng bi xun bi zeng wei zheng mao shan lin po dan meng ye sao kuai feng meng ju kuang lian zan chan you ji yan chan zan ling huan xi feng "
"zan li you ding qiu zhuo pei zhou yi gan yu jiu yin zui mao dan xu dou zhen fen yuan fu yun tai tian qia dou cu han gu su fa chou zai ming lao chuo chou you tong zhi xian jiang cheng yin tu jiao mei ku "
"suan lei pu fu hai yan shi niang wei lu lan yan tao pei zhan chun tan zui zhui cu kun ti xian du hu xu xing tan qiu chun yun fa ke sou mi quan chou cuo yun yong ang zha hai tang jiang piao chan ou li "
"zao lao yi jiang bu jiao xi tan fa nong yi li ju yan yi niang ru xun shou yan ling mi mi niang xin jiao shi mi yan bian cai shi you shi shi li zhong ye liang li jin jin ga yi liao dao zhao ding po qiu "
"he fu zhen zhi ba luan fu nai diao shan qiao kou chuan zi fan yu wu gan gang qi mang ren di si xi yi chai shi tu xi nv qian qiu jian zhao ya jin ba fang chen xing dou yue zhong fu pi na qin e jue dun "
"gou yin qian ban sa ren chao niu fen yun yi qin pi guo hong yin jun diao yi zhong xi gai ri huo tai kang yuan lu ngag wen duo zi ni tu shi min gu ke ling bing si gu bo pi yu si zuo bu you dian jia zhen "
"shi shi tie ju chan yi tuo xuan zhao bao he bi sheng zu shi bo zhu chi za po tong qian fu zhai mao qian fu li yue pi yang ban bo jie gou shu zheng mu ni nie di jia mu tan shen yi si kuang ka bei jian "
"tong xing hong jiao chi er ge ping shi mou ha yin jun zhou chong xiang tong mo lei ji si xu ren zun zhi qiong shan li xian jian quan pi yi zhu hou ming kua tiao gua xian xiu jun cha lao ji pi ru mi yi "
"yin guang an diu you se kao qian luan si ngai diao han rui zhi keng qiu xiao zhe xiu zang ti cuo gua gong yong dou lv mei lang wan xin jun bei wu su yu chan ting bo han jia hong juan feng chan wan zhi "
"tuo juan wu yu tiao kuang zhuo lue jing qin shen han lue ye chu zeng ju xian e mang pu li pan rui cheng gao li te bing zhu zhen tu liu zui ju chang wan jian gang diao tao chang lun guo ling pi lu li "
"qing pou juan min zui peng an pi xian ya zhui lei a kong ta kun du wei chui zi zheng ben nie zong chun tian ding qi qian zhui ji yu jin guan mao chang tian xi lian diao gu cuo shu zhen lu meng lu hua "
"biao ga lai ken fang wu nai wan zan hu de xian uu huo liang fa men jie ying chi lian guo xian du tu wei zong fu rou ji e jun zhen ti zha hu yang duan xia yu keng sheng huang wei fu zhao cha qie shi hong "
"kui nuo mou qiao qiao hou tou zong huan ye min jian duan jian si kui hu xuan zhe jie zhen bian zhong zi xiu ye mei pai ai gai qian mei suo ta bang xia lian suo kai liu yao ta nou weng rong tang suo "
"qiang ge shuo chui bo pan da bi sang gang zi wu ying huang tiao liu kai sun sha sou jian gao zhen zhen lang yi yuan tang nie xi jia ge ma juan song zu suo uu feng wen na lu suo kou zu tuan xiu guan xuan "
"lian sou ao man mo luo bi wei liao di can zong yi ao ao keng qiang cui qi chang tang man yong chan feng jing biao shu lou xiu cong long zan zan cao li xia xi kang shuang beng zhang qian cheng lu hua ji "
"pu sui qiang po lin se xiu sa cheng kui si liu nao huang pie sui fan qiao quan yang tang xiang yu jiao zun liao qie lao dun tan zan ji jian zhong deng ya ying dun jue nou ti pu tie uu zhang ding shan "
"kai jian fei sui lu juan hui yu lian zhuo sao jian zhuo lei bi tie huan ye duo guo dang ju ben da bi yi ai zong xun diao zhu heng zhui ji ni he huo qing bin ying kui ning ru jian jian qian cha zhi mie "
"li lei ji zuan kuang shang peng la du shuo chuo lv biao bao lu xian kuan long e lu xin jian lan bo qian yao chan xiang jian xi guan cang nie lei cuan qu pan luo zuan luan zao yi jue tang zhu lan jin ga "
"yi zhen ding zhao po liao tu qian chuan shan sa fan diao men nv yang chai xing gai bu tai ju dun chao zhong na bei gang ban qian yue qin jun wu gou kang fang huo dou niu ba yu qian zheng qian gu bo ke "
"po bu bo yue zuan mu tan jia dian you tie bo ling shuo qian mao bao shi xuan tuo bi ni pi duo xing kao lao er mang ya you cheng jia ye nao zhi dang tong lv diao yin kai zha zhu xian ting diu gua hua "
"quan sha ha diao ge ming zheng se jiao yi chan chong tang an yin ru zhu lao pu wu lai te lian keng xiao suo li zeng chu guo gao e xiu cuo lue feng xin liu kai jian rui ti lang qin ju a qiang zhe nuo cuo "
"mao ben qi de ke kun chang xi gu luo chui zhui jin zhi xian juan huo pou xian ding jian ju meng zi qie ying kai qiang si e cha qiao zhong duan sou huang huan ai du mei lou zi fei mei mo zhen bo ge nie "
"tang juan nie na liu gao bang yi jia bin rong biao tang man luo beng yong jing di zu xuan liao tan jue liao pu lu dun lan pu chuan qiang deng huo lei huan zhuo lian yi cha biao la chan xiang chang chang "
"jiu ao die jue liao mi chang men ma shuan shan shan men yan bi bi bi shan kai kang beng hong run san xian xian jian min xia shui dou zha nao zhan peng xia ling bian bi run he guan ge he fa chu hong gui "
"min seo kun liang lv ting sha ju yue yue chan qu lin chang sha kun yan wen yan yan hun yu wen xiang bao juan qu yao wen ban an wei yin kuo que lan she quan phdeng tian nie ta kai he que chuang guan dou "
"qi kui tang guan piao kan xi hui chan pi dang huan ta wen uu men shuan shan yan han bi wen chuang run wei xian hong jian min kang men zha nao gui wen ta min lv kai fa ge he kun jiu yue liang she yu yan "
"chang xi wen hun yan yan chan lan qu hui kuo que he tian ta que kan huan fu fu le dui xin qian wei gai yi yin yang dou e sheng ban pei keng yun ruan zhi pi jing fang yang yin zhen jie cheng ai qu di zu "
"zuo dian ling a tuo tuo po bing fu ji lu long chen jing duo lou mo jiang shu duo xian er gui yu gai shan jun qiao jing chun fu bi xia shan sheng zhi pu dou yuan zhen chu xian dao nie yun xian pei pei "
"zou qi dui lun yin ju chui chen pi ling tao xian lu sheng xian yin du yang reng xia chong yan yin yu di yu long wei wei nie dui sui an huang jie sui yin ai yan duo ge yun wu kui ai xi tang ji zhang dao "
"ao xi yin sa rao lin tui deng pi sui sui yu xian fen ni er ji dao xi yin zhi duo long xi dai li li cui que zhi sun jun nan yi que yan qin qian xiong ya ji gu huan zhi gou juan ci yong ju chu hu za luo "
"yu chou diao sui han huo shuang huan chu za yong ji xi chou liu li nan xue za ji ji yu xu xue na fou xi mu wen fen fang yun li chi yang ling lei an bao meng dian dang hu wu diao xu ji mu chen xiao sha "
"ting zhen pei mei ling qi zhou huo sha fei hong zhan yin ni zhu tun lin ling dong ying wu ling shuang ling xia hong yin mai mai yun liu meng bin wu wei kuo yin xi yi ai dan teng san yu lu long dai ji "
"pang yang ba pi wei uu xi ji mai mao meng lei li sui ai fei dai long ling ai feng li bao he he he bing qing qing liang tian zhen jing cheng jing jing liang dian jing tian fei fei kao mi mian mian bao "
"yan mian hui yan ge ding cha qian ren di du wu ren qin jin xue niu ba yin sa na mo zu da ban xie yao tao bi jie hong pao yang bing yin ge tao ji xie an an hen gong qia da qiao ting man bian sui tiao "
"qiao juan kong beng ta shang bi kuo ju la die rou bang eng qiu qiu he shao mu ju jian bian di jian on tao gou ta bei xie pan ge bi kuo tang lou gui qiao xue ji jian jiang chan da hu xian qian du wa jian "
"lan wei ren fu mei juan ge wei qiao han chang kuo rou yun she wei ge bai tao gou yun gao bi xue hui du wa du wei ren fu han wei yun tao jiu jiu xian xie xian ji yin za yun shao le peng huang ying yun "
"peng an yin xiang hu ye ding qing qiu xiang shun han xu yi xu gu song kui qi hang yu wan ban dun di dian pan po ling che jing lei han qiao an e wei jie kuo shen yi yi hai dui yu ping lei fu jia tou pou "
"kui jia luo ting cheng ying yun hu han jing tui tui pin lai tui zi zi chui ding lai tan han qian ke cui jiong qin yi sai ti e e yan hun yan yong zhuan yan xian xin yi yuan sang dian dian jiang kua lei "
"lao piao zhuai man cu qiao hao qiao gu xun yan hui chan ru meng bin xian pin lu lan nie quan ye ding qing han xiang shun xu xu wan gu dun qi ban song hang yu lu ling po jing jie jia ting he ying jiong "
"hai yi pin pou tui han ying ying ke ti yong e zhuan yan e nie man dian sang hao lei chan ru pin quan feng diao gua fu xia zhan pao sa ba tai lie gua xuan xiao ju biao si wei yang yao sou kai sao fan liu "
"xi liao piao piao liu biao biao biao liao biao se feng xiu feng yang zhan pao sa ju si sou yao liu piao biao biao fei fan fei fei shi shi can ji ding si tuo gan sun xiang tun ren yu yang chi yin fan fan "
"can yin zhu yi zha bi jie tao bao ci tie si bao shi duo hai ren tian jiao he bing yao tong ci xiang yang juan er yan le xi can bo nei e bu jun dou su yu xi yao hun guo chi jian zhui bing xian bu ye dan "
"fei zhang wei guan e nuan hun hu huang tie hui zhan hou he tang fen wei gu zha song tang bo gao xi kui liu sou xian ye wen mo tang man bi yu xiu jin san kui zhuan shan xi dan yi ji rao cheng yong tao "
"wei xiang zhan fen hai meng yan mo chan xiang luo zan nang shi ding ji tuo tang tun xi ren yu shi fan yin jian shi bao si duo yi er rao xiang he ge jiao xi bing bo dou e yu nei jun guo hun xian guan zha "
"kui gu sou chan ye mo bo liu xiu jin man san zhuan nang shou kui xu xiang fen bo ni bi bo tu han fei jian an ai fu xian yun xin fen pin xin ma yu feng han di tuo tuo chi xun zhu zhi pei xin ri sa yun "
"wen zhi dan lv you bo bao jue tuo yi qu pu qu jiong po zhao yuan peng zhou ju zhu nu ju pi zu jia ling zhen tai fu yang shi bi tuo tuo si liu ma pian tao zhi rong teng dong xun quan shen jiong er hai bo "
"zhu yin luo zhou dan hai liu ju song qin mang liang han tu xuan tui jun e cheng xing si lu zhui zhou she pian kun tao lai zong ke qi qi yan fei sao yan ge yao wu pian cong pian qian fei huang qian huo "
"yu ti quan xia zong kui rou si gua tuo gui sou qian cheng zhi liu peng teng xi cao du yan yuan zou sao shan qi zhi shuang lu xi luo zhang mo ao can piao cong qu bi zhi yu xu hua bo su xiao lin zhan dun "
"liu tuo ceng dian jiao tie yan luo zhan jing yi ye tuo pin zhou yan long lv teng xiang ji shuang ju xi huan li biao ma yu tuo xun chi qu ri bo lv zu shi si fu ju zhou zhu tuo nu jia yi tai xiao ma yin "
"jiao hua luo hai pian biao li cheng yan xing qin jun qi qi ke zhui zong su can pian zhi kui sao wu ao liu qian shan piao luo cong chan zhou ji shuang xiang gu wan wan wan yu gan yi ang gu jie bao bei ci "
"ti di ku hai jiao hou kua ge tui geng pian bi ke ge yu sui lou bo xiao pang jue cuo kuan bin mo liao lou xiao du zang sui ti bin kuan lu gao gao qiao kao qiao lao sao biao kun kun ti fang xiu ran mao "
"dan kun bin fa tiao pi zi fa ran ti bao bi mao fu er rong qu gong xiu kuo ji peng zhua shao sha ti li bin zong ti peng song zheng quan zong shun jian duo hu la jiu qi lian zhen bin peng ma san man man "
"seng xu lie qian qian nang huan kuai ning bin lie rang dou dou nao hong xi dou han dou dou jiu chang yu yu ge yan fu xin gui zeng liu gui shang yu gui mei qi qi ga kuai hun ba po mei xu yan xiao liang "
"yu zhui qi wang liang wei gan chi piao bi mo qi xu chou yan zhan yu dao ren ji ba hong tuo diao ji xu hua ji sha hang tun mo jie shen ban yuan bi lu wen hu lu shi fang fen na you pian mo he xia qu han "
"pi ling tuo ba qiu ping fu bi ci wei ju diao bo you gun pi nian zheng tai bao fu zha ju gu shi dong chou ta jie shu hou xiang er an wei zhao zhu yin lie luo tong yi yi bing wei jiao ku gui xian ge hui "
"lao fu kao xiu duo jun ti mian shao zha suo qin yu nei zhe gun geng su wu qiu shan pu huan tiao li sha sha kao meng cheng li zou xi yong shen zi qi qing xiang nei chun ji diao qie gu zhou dong lai fei "
"ni yi kun lu jiu chang jing lun ling zou li meng zong zhi nian hu yu di shi shen huan ti hou xing zhu la zong ji bian bian huan quan zei wei wei yu chun rou die huang lian yan qiu qiu jian bi e yang fu "
"sai jian xia tuo hu shi ruo xuan wen jian hao wu pang sao liu ma shi shi guan zi teng ta yao ge yong qian qi wen ruo shen lian ao le hui min ji tiao qu jian can man xi qiu biao ji ji zhu jiang xiu zhuan "
"yong zhang kang xue bie yu qu xiang bo jiao xun su huang zun shan shan fan jue lin xun miao xi zeng xiang fen guan hou kuai zei sao shan gan gui sheng li chang lei shu ai ru ji yu hu shu li la li mie "
"zhen xiang e lu guan li xian yu dao ji you tun lu fang ba he ba ping nian lu you zha fu bo bao hou pi tai gui jie kao wei er tong zei hou kuai ji jiao xian zha xiang xun geng li lian jian li shi tiao "
"gun sha huan jun ji yong qing ling qi zou fei kun chang gu ni nian diao jing can shi zi fen die bi chang ti wen wei sai e qiu fu huang quan jiang bian sao ao qi ta guan yao pang jian le biao xue bie man "
"min yong wei xi jue shan lin zun hu gan li shan guan niao yi fu li jiu bu yan fu diao ji feng ru han shi feng ming bao yuan zhi hu qin fu fen wen qian shi yu fou yao jue jue pi huan zhen bao yan ya "
"zheng fang feng wen ou dai jia ru ling bi fu tuo min li bian zhi ge yuan ci gou xiao chi dan ju yao gu zhong yu yang yu ya die yu tian ying dui wu er gua ai zhi yan heng xiao jia lie zhu xiang yi hong "
"lu ru mou ge ren jiao xiu zhou chi luo heng nian e luan jia ji tu juan tuo pu wu juan yu bo jun jun bi xi jun ju tu jing ti e e kuang hu wu shen chi jiao pan lu pi shu fu an zhuo peng qiu qian bei diao "
"lu que jian ju tu ya yuan qi li ye zhui kong duo kun sheng qi jing yi yi qing zi lai dong qi chun geng ju qu yi zun ji shu uu chi miao rou ya qiu ti hu ti e jie mao fu chun tu yan he yuan bian kun mei "
"hu ying chuan wu ju dong cang fang hu ying yuan xian weng shi he chu tang xia ruo liu ji hu jian sun han ci ci yi yao yan ji li tian kou ti ti yi tu ma xiao gao tian chen ji tuan zhe ao yao yi ou chi "
"zhi liu yong lv bi shuang zhuo yu wu jue yin tan si jiao yi hua bi ying su huang fan jiao liao yan gao jiu xian xian tu mai zun yu ying lu tuan xian xue yi pi shu luo xi yi ji ze yu zhan ye yang bi ning "
"hu mi ying meng di yue yu lei bu lu he long shuang yue ying huan qu li luan niao jiu ji yuan ming shi ou ya cang bao zhen gu dong lu ya xiao yang ling chi gou yuan xue tuo si zhi er gua xiu heng zhou ge "
"luan hong wu bo li juan hu e yu xian ti wu que miao an kun bei peng qian chun geng yuan su hu he e hu qiu ci mei wu yi yao weng liu ji yi jian he yi ying zhe liu liao jiao jiu yu lu huan zhan ying hu "
"meng huan shuang lu jin ling jian xian cuo jian jian yan cuo lu you cu ji biao cu pao cu jun zhu jian mi mi yu liu chen qun lin ni qi lu jiu jun jing li xiang xian jia mi li she zhang lin jing qi ling "
"yan cu mai mai he chao fu mian mian fu pao qu qu mou fu xian lai qu mian chi feng fu qu mian ma me me hui mo zou nun fen huang huang jin guang tian tou hong hua kuang hong shu li nian chi hei hei yi "
"qian dan xi tun mo mo qian dai chu you dian yi xia yan qu mei yan qing yue li dang du can yan jian yan zhen an zhen zhun can yi mei zhan yan du lu xian fen fu fu meng meng yuan cu qu chao wa zhu zhi "
"meng ao bie tuo bi yuan chao tuo ding jiong nai ding zi gu gu dong fen tao yuan pi chang gao cao yuan tang teng shu shu fen fei wen ba diao tuo zhong qu sheng shi you shi ting wu ju jing hun xi yan tu "
"si xi xian yan lei bi yao qiu han wu wu hou xie he zha xiu weng zha nong nang qi zhai ji ji ji ji qi ji chi chen chen he ya yin xie bao ze shi zi chi yan ju tiao ling ling chu quan xie yin nie jiu yao "
"chuo yun wu chu qi ni ce chuo qu yun yan yu e wo yi cuo zou dian chu jin ya chi chen he yin ju ling bao tiao zi yin wu chuo qu wo long pang gong pang yan long long gong kan da ling da long gong kan gui "
"qiu bie gui yue chui he jiao xie yu";

ZhToPY *ZhToPY::self = NULL;

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> split_name(std::string name) {
    std::vector<std::string> words;
    for (size_t j = 0; j < name.length();) {
        size_t cplen = 1;
        if ((name[j] & 0xf8) == 0xf0)
            cplen = 4;
        else if ((name[j] & 0xf0) == 0xe0)
            cplen = 3;
        else if ((name[j] & 0xe0) == 0xc0)
            cplen = 2;
        if ((j + cplen) > name.length())
            cplen = 1;
        words.push_back(name.substr(j, cplen));
        j += cplen;
    }
    return words;
}

static bool check_length(unsigned int start, unsigned int offset, unsigned int end) {
    if (start + offset >= end) {
        return false;
    }
    return true;
}

static bool utf8_to_unicode(const std::string &utf8, std::vector<unsigned int> &unicode) {
    unsigned int utf8length = utf8.size();
    unsigned int utf8_cursor = 0;
    unsigned int offset;
    unsigned char* p;
    unsigned int e;
    unicode.clear();
    while (utf8_cursor < utf8length) {
        p = (unsigned char*)&utf8[utf8_cursor];
        if (*p < 0xC0) {
            offset = 0;
            e = p[0];
        }
        else if (*p < 0xE0) {
            /*2:<11000000>*/
            offset = 1;
            if (not check_length(utf8_cursor, offset, utf8length)) return false;
            e = (p[0] & 0x1f) << 6;
            e |= (p[1] & 0x3f);
        }
        else if (*p < 0xF0) {
            /*3:<11100000>*/
            offset = 2;
            if (not check_length(utf8_cursor, offset, utf8length)) return false;
            e = (p[0] & 0x0f) << 12;
            e |= (p[1] & 0x3f) << 6;
            e |= (p[2] & 0x3f);
        }
        else if (*p < 0xF8) {
            /*4:<11110000>*/
            offset = 3;
            if (not check_length(utf8_cursor, offset, utf8length)) return false;
            e = (p[0] & 0x07) << 18;
            e |= (p[1] & 0x3f) << 12;
            e |= (p[2] & 0x3f) << 6;
            e |= (p[3] & 0x3f);
        }
        else if (*p < 0xFC) {
            /*5:<11111000>*/
            offset = 4;
            if (not check_length(utf8_cursor, offset, utf8length)) return false;
            e = (p[0] & 0x03) << 24;
            e |= (p[1] & 0x3f) << 18;
            e |= (p[2] & 0x3f) << 12;
            e |= (p[3] & 0x3f) << 6;
            e |= (p[4] & 0x3f);
        }
        else {
            /*6:<11111100>*/
            offset = 5;
            if (not check_length(utf8_cursor, offset, utf8length)) return false;
            e = (p[0] & 0x01) << 30;
            e |= (p[1] & 0x3f) << 24;
            e |= (p[2] & 0x3f) << 18;
            e |= (p[3] & 0x3f) << 12;
            e |= (p[4] & 0x3f) << 6;
            e |= (p[5] & 0x3f);
        }
        unicode.push_back(e);
        utf8_cursor += offset + 1;
    }
    return true;
}

int get_code_point(const std::string &name) {
    if (name.empty()) return 0;
    int name_code_point = 0;

    std::vector<unsigned int> unicode;
    utf8_to_unicode(name,unicode);

    if (!unicode.empty()) name_code_point = *unicode.begin();

    return name_code_point;
}

ZhToPY *ZhToPY::instance()
{
    if (self == NULL) {
        self = new ZhToPY();
    }

    return self;
}

ZhToPY::ZhToPY()
{
    //
    listPY = split(pinyinArrStr,' ');

    //加载简拼数组
    listStrJP.append("YDYQSXMWZSSXJBYMGCCZQPSSQBYCDSCDQLDYLYBSSJGYZZJJFKCCLZDHWDWZJLJPFYYNWJJTMYHZWZHFLZPPQHGSCYYYNJQYXXGJ");
    listStrJP.append("HHSDSJNKKTMOMLCRXYPSNQSECCQZGGLLYJLMYZZSECYKYYHQWJSSGGYXYZYJWWKDJHYCHMYXJTLXJYQBYXZLDWRDJRWYSRLDZJPC");
    listStrJP.append("BZJJBRCFTLECZSTZFXXZHTRQHYBDLYCZSSYMMRFMYQZPWWJJYFCRWFDFZQPYDDWYXKYJAWJFFXYPSFTZYHHYZYSWCJYXSCLCXXWZ");
    listStrJP.append("ZXNBGNNXBXLZSZSBSGPYSYZDHMDZBQBZCWDZZYYTZHBTSYYBZGNTNXQYWQSKBPHHLXGYBFMJEBJHHGQTJCYSXSTKZHLYCKGLYSMZ");
    listStrJP.append("XYALMELDCCXGZYRJXSDLTYZCQKCNNJWHJTZZCQLJSTSTBNXBTYXCEQXGKWJYFLZQLYHYXSPSFXLMPBYSXXXYDJCZYLLLSJXFHJXP");
    listStrJP.append("JBTFFYABYXBHZZBJYZLWLCZGGBTSSMDTJZXPTHYQTGLJSCQFZKJZJQNLZWLSLHDZBWJNCJZYZSQQYCQYRZCJJWYBRTWPYFTWEXCS");
    listStrJP.append("KDZCTBZHYZZYYJXZCFFZZMJYXXSDZZOTTBZLQWFCKSZSXFYRLNYJMBDTHJXSQQCCSBXYYTSYFBXDZTGBCNSLCYZZPSAZYZZSCJCS");
    listStrJP.append("HZQYDXLBPJLLMQXTYDZXSQJTZPXLCGLQTZWJBHCTSYJSFXYEJJTLBGXSXJMYJQQPFZASYJNTYDJXKJCDJSZCBARTDCLYJQMWNQNC");
    listStrJP.append("LLLKBYBZZSYHQQLTWLCCXTXLLZNTYLNEWYZYXCZXXGRKRMTCNDNJTSYYSSDQDGHSDBJGHRWRQLYBGLXHLGTGXBQJDZPYJSJYJCTM");
    listStrJP.append("RNYMGRZJCZGJMZMGXMPRYXKJNYMSGMZJYMKMFXMLDTGFBHCJHKYLPFMDXLQJJSMTQGZSJLQDLDGJYCALCMZCSDJLLNXDJFFFFJCZ");
    listStrJP.append("FMZFFPFKHKGDPSXKTACJDHHZDDCRRCFQYJKQCCWJDXHWJLYLLZGCFCQDSMLZPBJJPLSBCJGGDCKKDEZSQCCKJGCGKDJTJDLZYCXK");
    listStrJP.append("LQSCGJCLTFPCQCZGWPJDQYZJJBYJHSJDZWGFSJGZKQCCZLLPSPKJGQJHZZLJPLGJGJJTHJJYJZCZMLZLYQBGJWMLJKXZDZNJQSYZ");
    listStrJP.append("MLJLLJKYWXMKJLHSKJGBMCLYYMKXJQLBMLLKMDXXKWYXYSLMLPSJQQJQXYXFJTJDXMXXLLCXQBSYJBGWYMBGGBCYXPJYGPEPFGDJ");
    listStrJP.append("GBHBNSQJYZJKJKHXQFGQZKFHYGKHDKLLSDJQXPQYKYBNQSXQNSZSWHBSXWHXWBZZXDMNSJBSBKBBZKLYLXGWXDRWYQZMYWSJQLCJ");
    listStrJP.append("XXJXKJEQXSCYETLZHLYYYSDZPAQYZCMTLSHTZCFYZYXYLJSDCJQAGYSLCQLYYYSHMRQQKLDXZSCSSSYDYCJYSFSJBFRSSZQSBXXP");
    listStrJP.append("XJYSDRCKGJLGDKZJZBDKTCSYQPYHSTCLDJDHMXMCGXYZHJDDTMHLTXZXYLYMOHYJCLTYFBQQXPFBDFHHTKSQHZYYWCNXXCRWHOWG");
    listStrJP.append("YJLEGWDQCWGFJYCSNTMYTOLBYGWQWESJPWNMLRYDZSZTXYQPZGCWXHNGPYXSHMYQJXZTDPPBFYHZHTJYFDZWKGKZBLDNTSXHQEEG");
    listStrJP.append("ZZYLZMMZYJZGXZXKHKSTXNXXWYLYAPSTHXDWHZYMPXAGKYDXBHNHXKDPJNMYHYLPMGOCSLNZHKXXLPZZLBMLSFBHHGYGYYGGBHSC");
    listStrJP.append("YAQTYWLXTZQCEZYDQDQMMHTKLLSZHLSJZWFYHQSWSCWLQAZYNYTLSXTHAZNKZZSZZLAXXZWWCTGQQTDDYZTCCHYQZFLXPSLZYGPZ");
    listStrJP.append("SZNGLNDQTBDLXGTCTAJDKYWNSYZLJHHZZCWNYYZYWMHYCHHYXHJKZWSXHZYXLYSKQYSPSLYZWMYPPKBYGLKZHTYXAXQSYSHXASMC");
    listStrJP.append("HKDSCRSWJPWXSGZJLWWSCHSJHSQNHCSEGNDAQTBAALZZMSSTDQJCJKTSCJAXPLGGXHHGXXZCXPDMMHLDGTYBYSJMXHMRCPXXJZCK");
    listStrJP.append("ZXSHMLQXXTTHXWZFKHCCZDYTCJYXQHLXDHYPJQXYLSYYDZOZJNYXQEZYSQYAYXWYPDGXDDXSPPYZNDLTWRHXYDXZZJHTCXMCZLHP");
    listStrJP.append("YYYYMHZLLHNXMYLLLMDCPPXHMXDKYCYRDLTXJCHHZZXZLCCLYLNZSHZJZZLNNRLWHYQSNJHXYNTTTKYJPYCHHYEGKCTTWLGQRLGG");
    listStrJP.append("TGTYGYHPYHYLQYQGCWYQKPYYYTTTTLHYHLLTYTTSPLKYZXGZWGPYDSSZZDQXSKCQNMJJZZBXYQMJRTFFBTKHZKBXLJJKDXJTLBWF");
    listStrJP.append("ZPPTKQTZTGPDGNTPJYFALQMKGXBDCLZFHZCLLLLADPMXDJHLCCLGYHDZFGYDDGCYYFGYDXKSSEBDHYKDKDKHNAXXYBPBYYHXZQGA");
    listStrJP.append("FFQYJXDMLJCSQZLLPCHBSXGJYNDYBYQSPZWJLZKSDDTACTBXZDYZYPJZQSJNKKTKNJDJGYYPGTLFYQKASDNTCYHBLWDZHBBYDWJR");
    listStrJP.append("YGKZYHEYYFJMSDTYFZJJHGCXPLXHLDWXXJKYTCYKSSSMTWCTTQZLPBSZDZWZXGZAGYKTYWXLHLSPBCLLOQMMZSSLCMBJCSZZKYDC");
    listStrJP.append("ZJGQQDSMCYTZQQLWZQZXSSFPTTFQMDDZDSHDTDWFHTDYZJYQJQKYPBDJYYXTLJHDRQXXXHAYDHRJLKLYTWHLLRLLRCXYLBWSRSZZ");
    listStrJP.append("SYMKZZHHKYHXKSMDSYDYCJPBZBSQLFCXXXNXKXWYWSDZYQOGGQMMYHCDZTTFJYYBGSTTTYBYKJDHKYXBELHTYPJQNFXFDYKZHQKZ");
    listStrJP.append("BYJTZBXHFDXKDASWTAWAJLDYJSFHBLDNNTNQJTJNCHXFJSRFWHZFMDRYJYJWZPDJKZYJYMPCYZNYNXFBYTFYFWYGDBNZZZDNYTXZ");
    listStrJP.append("EMMQBSQEHXFZMBMFLZZSRXYMJGSXWZJSPRYDJSJGXHJJGLJJYNZZJXHGXKYMLPYYYCXYTWQZSWHWLYRJLPXSLSXMFSWWKLCTNXNY");
    listStrJP.append("NPSJSZHDZEPTXMYYWXYYSYWLXJQZQXZDCLEEELMCPJPCLWBXSQHFWWTFFJTNQJHJQDXHWLBYZNFJLALKYYJLDXHHYCSTYYWNRJYX");
    listStrJP.append("YWTRMDRQHWQCMFJDYZMHMYYXJWMYZQZXTLMRSPWWCHAQBXYGZYPXYYRRCLMPYMGKSJSZYSRMYJSNXTPLNBAPPYPYLXYYZKYNLDZY");
    listStrJP.append("JZCZNNLMZHHARQMPGWQTZMXXMLLHGDZXYHXKYXYCJMFFYYHJFSBSSQLXXNDYCANNMTCJCYPRRNYTYQNYYMBMSXNDLYLYSLJRLXYS");
    listStrJP.append("XQMLLYZLZJJJKYZZCSFBZXXMSTBJGNXYZHLXNMCWSCYZYFZLXBRNNNYLBNRTGZQYSATSWRYHYJZMZDHZGZDWYBSSCSKXSYHYTXXG");
    listStrJP.append("CQGXZZSHYXJSCRHMKKBXCZJYJYMKQHZJFNBHMQHYSNJNZYBKNQMCLGQHWLZNZSWXKHLJHYYBQLBFCDSXDLDSPFZPSKJYZWZXZDDX");
    listStrJP.append("JSMMEGJSCSSMGCLXXKYYYLNYPWWWGYDKZJGGGZGGSYCKNJWNJPCXBJJTQTJWDSSPJXZXNZXUMELPXFSXTLLXCLJXJJLJZXCTPSWX");
    listStrJP.append("LYDHLYQRWHSYCSQYYBYAYWJJJQFWQCQQCJQGXALDBZZYJGKGXPLTZYFXJLTPADKYQHPMATLCPDCKBMTXYBHKLENXDLEEGQDYMSAW");
    listStrJP.append("HZMLJTWYGXLYQZLJEEYYBQQFFNLYXRDSCTGJGXYYNKLLYQKCCTLHJLQMKKZGCYYGLLLJDZGYDHZWXPYSJBZKDZGYZZHYWYFQYTYZ");
    listStrJP.append("SZYEZZLYMHJJHTSMQWYZLKYYWZCSRKQYTLTDXWCTYJKLWSQZWBDCQYNCJSRSZJLKCDCDTLZZZACQQZZDDXYPLXZBQJYLZLLLQDDZ");
    listStrJP.append("QJYJYJZYXNYYYNYJXKXDAZWYRDLJYYYRJLXLLDYXJCYWYWNQCCLDDNYYYNYCKCZHXXCCLGZQJGKWPPCQQJYSBZZXYJSQPXJPZBSB");
    listStrJP.append("DSFNSFPZXHDWZTDWPPTFLZZBZDMYYPQJRSDZSQZSQXBDGCPZSWDWCSQZGMDHZXMWWFYBPDGPHTMJTHZSMMBGZMBZJCFZWFZBBZMQ");
    listStrJP.append("CFMBDMCJXLGPNJBBXGYHYYJGPTZGZMQBQTCGYXJXLWZKYDPDYMGCFTPFXYZTZXDZXTGKMTYBBCLBJASKYTSSQYYMSZXFJEWLXLLS");
    listStrJP.append("ZBQJJJAKLYLXLYCCTSXMCWFKKKBSXLLLLJYXTYLTJYYTDPJHNHNNKBYQNFQYYZBYYESSESSGDYHFHWTCJBSDZZTFDMXHCNJZYMQW");
    listStrJP.append("SRYJDZJQPDQBBSTJGGFBKJBXTGQHNGWJXJGDLLTHZHHYYYYYYSXWTYYYCCBDBPYPZYCCZYJPZYWCBDLFWZCWJDXXHYHLHWZZXJTC");
    listStrJP.append("ZLCDPXUJCZZZLYXJJTXPHFXWPYWXZPTDZZBDZCYHJHMLXBQXSBYLRDTGJRRCTTTHYTCZWMXFYTWWZCWJWXJYWCSKYBZSCCTZQNHX");
    listStrJP.append("NWXXKHKFHTSWOCCJYBCMPZZYKBNNZPBZHHZDLSYDDYTYFJPXYNGFXBYQXCBHXCPSXTYZDMKYSNXSXLHKMZXLYHDHKWHXXSSKQYHH");
    listStrJP.append("CJYXGLHZXCSNHEKDTGZXQYPKDHEXTYKCNYMYYYPKQYYYKXZLTHJQTBYQHXBMYHSQCKWWYLLHCYYLNNEQXQWMCFBDCCMLJGGXDQKT");
    listStrJP.append("LXKGNQCDGZJWYJJLYHHQTTTNWCHMXCXWHWSZJYDJCCDBQCDGDNYXZTHCQRXCBHZTQCBXWGQWYYBXHMBYMYQTYEXMQKYAQYRGYZSL");
    listStrJP.append("FYKKQHYSSQYSHJGJCNXKZYCXSBXYXHYYLSTYCXQTHYSMGSCPMMGCCCCCMTZTASMGQZJHKLOSQYLSWTMXSYQKDZLJQQYPLSYCZTCQ");
    listStrJP.append("QPBBQJZCLPKHQZYYXXDTDDTSJCXFFLLCHQXMJLWCJCXTSPYCXNDTJSHJWXDQQJSKXYAMYLSJHMLALYKXCYYDMNMDQMXMCZNNCYBZ");
    listStrJP.append("KKYFLMCHCMLHXRCJJHSYLNMTJZGZGYWJXSRXCWJGJQHQZDQJDCJJZKJKGDZQGJJYJYLXZXXCDQHHHEYTMHLFSBDJSYYSHFYSTCZQ");
    listStrJP.append("LPBDRFRZTZYKYWHSZYQKWDQZRKMSYNBCRXQBJYFAZPZZEDZCJYWBCJWHYJBQSZYWRYSZPTDKZPFPBNZTKLQYHBBZPNPPTYZZYBQN");
    listStrJP.append("YDCPJMMCYCQMCYFZZDCMNLFPBPLNGQJTBTTNJZPZBBZNJKLJQYLNBZQHKSJZNGGQSZZKYXSHPZSNBCGZKDDZQANZHJKDRTLZLSWJ");
    listStrJP.append("LJZLYWTJNDJZJHXYAYNCBGTZCSSQMNJPJYTYSWXZFKWJQTKHTZPLBHSNJZSYZBWZZZZLSYLSBJHDWWQPSLMMFBJDWAQYZTCJTBNN");
    listStrJP.append("WZXQXCDSLQGDSDPDZHJTQQPSWLYYJZLGYXYZLCTCBJTKTYCZJTQKBSJLGMGZDMCSGPYNJZYQYYKNXRPWSZXMTNCSZZYXYBYHYZAX");
    listStrJP.append("YWQCJTLLCKJJTJHGDXDXYQYZZBYWDLWQCGLZGJGQRQZCZSSBCRPCSKYDZNXJSQGXSSJMYDNSTZTPBDLTKZWXQWQTZEXNQCZGWEZK");
    listStrJP.append("SSBYBRTSSSLCCGBPSZQSZLCCGLLLZXHZQTHCZMQGYZQZNMCOCSZJMMZSQPJYGQLJYJPPLDXRGZYXCCSXHSHGTZNLZWZKJCXTCFCJ");
    listStrJP.append("XLBMQBCZZWPQDNHXLJCTHYZLGYLNLSZZPCXDSCQQHJQKSXZPBAJYEMSMJTZDXLCJYRYYNWJBNGZZTMJXLTBSLYRZPYLSSCNXPHLL");
    listStrJP.append("HYLLQQZQLXYMRSYCXZLMMCZLTZSDWTJJLLNZGGQXPFSKYGYGHBFZPDKMWGHCXMSGDXJMCJZDYCABXJDLNBCDQYGSKYDQTXDJJYXM");
    listStrJP.append("SZQAZDZFSLQXYJSJZYLBTXXWXQQZBJZUFBBLYLWDSLJHXJYZJWTDJCZFQZQZZDZSXZZQLZCDZFJHYSPYMPQZMLPPLFFXJJNZZYLS");
    listStrJP.append("JEYQZFPFZKSYWJJJHRDJZZXTXXGLGHYDXCSKYSWMMZCWYBAZBJKSHFHJCXMHFQHYXXYZFTSJYZFXYXPZLCHMZMBXHZZSXYFYMNCW");
    listStrJP.append("DABAZLXKTCSHHXKXJJZJSTHYGXSXYYHHHJWXKZXSSBZZWHHHCWTZZZPJXSNXQQJGZYZYWLLCWXZFXXYXYHXMKYYSWSQMNLNAYCYS");
    listStrJP.append("PMJKHWCQHYLAJJMZXHMMCNZHBHXCLXTJPLTXYJHDYYLTTXFSZHYXXSJBJYAYRSMXYPLCKDUYHLXRLNLLSTYZYYQYGYHHSCCSMZCT");
    listStrJP.append("ZQXKYQFPYYRPFFLKQUNTSZLLZMWWTCQQYZWTLLMLMPWMBZSSTZRBPDDTLQJJBXZCSRZQQYGWCSXFWZLXCCRSZDZMCYGGDZQSGTJS");
    listStrJP.append("WLJMYMMZYHFBJDGYXCCPSHXNZCSBSJYJGJMPPWAFFYFNXHYZXZYLREMZGZCYZSSZDLLJCSQFNXZKPTXZGXJJGFMYYYSNBTYLBNLH");
    listStrJP.append("PFZDCYFBMGQRRSSSZXYSGTZRNYDZZCDGPJAFJFZKNZBLCZSZPSGCYCJSZLMLRSZBZZLDLSLLYSXSQZQLYXZLSKKBRXBRBZCYCXZZ");
    listStrJP.append("ZEEYFGKLZLYYHGZSGZLFJHGTGWKRAAJYZKZQTSSHJJXDCYZUYJLZYRZDQQHGJZXSSZBYKJPBFRTJXLLFQWJHYLQTYMBLPZDXTZYG");
    listStrJP.append("BDHZZRBGXHWNJTJXLKSCFSMWLSDQYSJTXKZSCFWJLBXFTZLLJZLLQBLSQMQQCGCZFPBPHZCZJLPYYGGDTGWDCFCZQYYYQYSSCLXZ");
    listStrJP.append("SKLZZZGFFCQNWGLHQYZJJCZLQZZYJPJZZBPDCCMHJGXDQDGDLZQMFGPSYTSDYFWWDJZJYSXYYCZCYHZWPBYKXRYLYBHKJKSFXTZJ");
    listStrJP.append("MMCKHLLTNYYMSYXYZPYJQYCSYCWMTJJKQYRHLLQXPSGTLYYCLJSCPXJYZFNMLRGJJTYZBXYZMSJYJHHFZQMSYXRSZCWTLRTQZSST");
    listStrJP.append("KXGQKGSPTGCZNJSJCQCXHMXGGZTQYDJKZDLBZSXJLHYQGGGTHQSZPYHJHHGYYGKGGCWJZZYLCZLXQSFTGZSLLLMLJSKCTBLLZZSZ");
    listStrJP.append("MMNYTPZSXQHJCJYQXYZXZQZCPSHKZZYSXCDFGMWQRLLQXRFZTLYSTCTMJCXJJXHJNXTNRZTZFQYHQGLLGCXSZSJDJLJCYDSJTLNY");
    listStrJP.append("XHSZXCGJZYQPYLFHDJSBPCCZHJJJQZJQDYBSSLLCMYTTMQTBHJQNNYGKYRQYQMZGCJKPDCGMYZHQLLSLLCLMHOLZGDYYFZSLJCQZ");
    listStrJP.append("LYLZQJESHNYLLJXGJXLYSYYYXNBZLJSSZCQQCJYLLZLTJYLLZLLBNYLGQCHXYYXOXCXQKYJXXXYKLXSXXYQXCYKQXQCSGYXXYQXY");
    listStrJP.append("GYTQOHXHXPYXXXULCYEYCHZZCBWQBBWJQZSCSZSSLZYLKDESJZWMYMCYTSDSXXSCJPQQSQYLYYZYCMDJDZYWCBTJSYDJKCYDDJLB");
    listStrJP.append("DJJSODZYSYXQQYXDHHGQQYQHDYXWGMMMAJDYBBBPPBCMUUPLJZSMTXERXJMHQNUTPJDCBSSMSSSTKJTSSMMTRCPLZSZMLQDSDMJM");
    listStrJP.append("QPNQDXCFYNBFSDQXYXHYAYKQYDDLQYYYSSZBYDSLNTFQTZQPZMCHDHCZCWFDXTMYQSPHQYYXSRGJCWTJTZZQMGWJJTJHTQJBBHWZ");
    listStrJP.append("PXXHYQFXXQYWYYHYSCDYDHHQMNMTMWCPBSZPPZZGLMZFOLLCFWHMMSJZTTDHZZYFFYTZZGZYSKYJXQYJZQBHMBZZLYGHGFMSHPZF");
    listStrJP.append("ZSNCLPBQSNJXZSLXXFPMTYJYGBXLLDLXPZJYZJYHHZCYWHJYLSJEXFSZZYWXKZJLUYDTMLYMQJPWXYHXSKTQJEZRPXXZHHMHWQPW");
    listStrJP.append("QLYJJQJJZSZCPHJLCHHNXJLQWZJHBMZYXBDHHYPZLHLHLGFWLCHYYTLHJXCJMSCPXSTKPNHQXSRTYXXTESYJCTLSSLSTDLLLWWYH");
    listStrJP.append("DHRJZSFGXTSYCZYNYHTDHWJSLHTZDQDJZXXQHGYLTZPHCSQFCLNJTCLZPFSTPDYNYLGMJLLYCQHYSSHCHYLHQYQTMZYPBYWRFQYK");
    listStrJP.append("QSYSLZDQJMPXYYSSRHZJNYWTQDFZBWWTWWRXCWHGYHXMKMYYYQMSMZHNGCEPMLQQMTCWCTMMPXJPJJHFXYYZSXZHTYBMSTSYJTTQ");
    listStrJP.append("QQYYLHYNPYQZLCYZHZWSMYLKFJXLWGXYPJYTYSYXYMZCKTTWLKSMZSYLMPWLZWXWQZSSAQSYXYRHSSNTSRAPXCPWCMGDXHXZDZYF");
    listStrJP.append("JHGZTTSBJHGYZSZYSMYCLLLXBTYXHBBZJKSSDMALXHYCFYGMQYPJYCQXJLLLJGSLZGQLYCJCCZOTYXMTMTTLLWTGPXYMZMKLPSZZ");
    listStrJP.append("ZXHKQYSXCTYJZYHXSHYXZKXLZWPSQPYHJWPJPWXQQYLXSDHMRSLZZYZWTTCYXYSZZSHBSCCSTPLWSSCJCHNLCGCHSSPHYLHFHHXJ");
    listStrJP.append("SXYLLNYLSZDHZXYLSXLWZYKCLDYAXZCMDDYSPJTQJZLNWQPSSSWCTSTSZLBLNXSMNYYMJQBQHRZWTYYDCHQLXKPZWBGQYBKFCMZW");
    listStrJP.append("PZLLYYLSZYDWHXPSBCMLJBSCGBHXLQHYRLJXYSWXWXZSLDFHLSLYNJLZYFLYJYCDRJLFSYZFSLLCQYQFGJYHYXZLYLMSTDJCYHBZ");
    listStrJP.append("LLNWLXXYGYYHSMGDHXXHHLZZJZXCZZZCYQZFNGWPYLCPKPYYPMCLQKDGXZGGWQBDXZZKZFBXXLZXJTPJPTTBYTSZZDWSLCHZHSLT");
    listStrJP.append("YXHQLHYXXXYYZYSWTXZKHLXZXZPYHGCHKCFSYHUTJRLXFJXPTZTWHPLYXFCRHXSHXKYXXYHZQDXQWULHYHMJTBFLKHTXCWHJFWJC");
    listStrJP.append("FPQRYQXCYYYQYGRPYWSGSUNGWCHKZDXYFLXXHJJBYZWTSXXNCYJJYMSWZJQRMHXZWFQSYLZJZGBHYNSLBGTTCSYBYXXWXYHXYYXN");
    listStrJP.append("SQYXMQYWRGYQLXBBZLJSYLPSYTJZYHYZAWLRORJMKSCZJXXXYXCHDYXRYXXJDTSQFXLYLTSFFYXLMTYJMJUYYYXLTZCSXQZQHZXL");
    listStrJP.append("YYXZHDNBRXXXJCTYHLBRLMBRLLAXKYLLLJLYXXLYCRYLCJTGJCMTLZLLCYZZPZPCYAWHJJFYBDYYZSMPCKZDQYQPBPCJPDCYZMDP");
    listStrJP.append("BCYYDYCNNPLMTMLRMFMMGWYZBSJGYGSMZQQQZTXMKQWGXLLPJGZBQCDJJJFPKJKCXBLJMSWMDTQJXLDLPPBXCWRCQFBFQJCZAHZG");
    listStrJP.append("MYKPHYYHZYKNDKZMBPJYXPXYHLFPNYYGXJDBKXNXHJMZJXSTRSTLDXSKZYSYBZXJLXYSLBZYSLHXJPFXPQNBYLLJQKYGZMCYZZYM");
    listStrJP.append("CCSLCLHZFWFWYXZMWSXTYNXJHPYYMCYSPMHYSMYDYSHQYZCHMJJMZCAAGCFJBBHPLYZYLXXSDJGXDHKXXTXXNBHRMLYJSLTXMRHN");
    listStrJP.append("LXQJXYZLLYSWQGDLBJHDCGJYQYCMHWFMJYBMBYJYJWYMDPWHXQLDYGPDFXXBCGJSPCKRSSYZJMSLBZZJFLJJJLGXZGYXYXLSZQYX");
    listStrJP.append("BEXYXHGCXBPLDYHWETTWWCJMBTXCHXYQXLLXFLYXLLJLSSFWDPZSMYJCLMWYTCZPCHQEKCQBWLCQYDPLQPPQZQFJQDJHYMMCXTXD");
    listStrJP.append("RMJWRHXCJZYLQXDYYNHYYHRSLSRSYWWZJYMTLTLLGTQCJZYABTCKZCJYCCQLJZQXALMZYHYWLWDXZXQDLLQSHGPJFJLJHJABCQZD");
    listStrJP.append("JGTKHSSTCYJLPSWZLXZXRWGLDLZRLZXTGSLLLLZLYXXWGDZYGBDPHZPBRLWSXQBPFDWOFMWHLYPCBJCCLDMBZPBZZLCYQXLDOMZB");
    listStrJP.append("LZWPDWYYGDSTTHCSQSCCRSSSYSLFYBFNTYJSZDFNDPDHDZZMBBLSLCMYFFGTJJQWFTMTPJWFNLBZCMMJTGBDZLQLPYFHYYMJYLSD");
    listStrJP.append("CHDZJWJCCTLJCLDTLJJCPDDSQDSSZYBNDBJLGGJZXSXNLYCYBJXQYCBYLZCFZPPGKCXZDZFZTJJFJSJXZBNZYJQTTYJYHTYCZHYM");
    listStrJP.append("DJXTTMPXSPLZCDWSLSHXYPZGTFMLCJTYCBPMGDKWYCYZCDSZZYHFLYCTYGWHKJYYLSJCXGYWJCBLLCSNDDBTZBSCLYZCZZSSQDLL");
    listStrJP.append("MQYYHFSLQLLXFTYHABXGWNYWYYPLLSDLDLLBJCYXJZMLHLJDXYYQYTDLLLBUGBFDFBBQJZZMDPJHGCLGMJJPGAEHHBWCQXAXHHHZ");
    listStrJP.append("CHXYPHJAXHLPHJPGPZJQCQZGJJZZUZDMQYYBZZPHYHYBWHAZYJHYKFGDPFQSDLZMLJXKXGALXZDAGLMDGXMWZQYXXDXXPFDMMSSY");
    listStrJP.append("MPFMDMMKXKSYZYSHDZKXSYSMMZZZMSYDNZZCZXFPLSTMZDNMXCKJMZTYYMZMZZMSXHHDCZJEMXXKLJSTLWLSQLYJZLLZJSSDPPMH");
    listStrJP.append("NLZJCZYHMXXHGZCJMDHXTKGRMXFWMCGMWKDTKSXQMMMFZZYDKMSCLCMPCGMHSPXQPZDSSLCXKYXTWLWJYAHZJGZQMCSNXYYMMPML");
    listStrJP.append("KJXMHLMLQMXCTKZMJQYSZJSYSZHSYJZJCDAJZYBSDQJZGWZQQXFKDMSDJLFWEHKZQKJPEYPZYSZCDWYJFFMZZYLTTDZZEFMZLBNP");
    listStrJP.append("PLPLPEPSZALLTYLKCKQZKGENQLWAGYXYDPXLHSXQQWQCQXQCLHYXXMLYCCWLYMQYSKGCHLCJNSZKPYZKCQZQLJPDMDZHLASXLBYD");
    listStrJP.append("WQLWDNBQCRYDDZTJYBKBWSZDXDTNPJDTCTQDFXQQMGNXECLTTBKPWSLCTYQLPWYZZKLPYGZCQQPLLKCCYLPQMZCZQCLJSLQZDJXL");
    listStrJP.append("DDHPZQDLJJXZQDXYZQKZLJCYQDYJPPYPQYKJYRMPCBYMCXKLLZLLFQPYLLLMBSGLCYSSLRSYSQTMXYXZQZFDZUYSYZTFFMZZSMZQ");
    listStrJP.append("HZSSCCMLYXWTPZGXZJGZGSJSGKDDHTQGGZLLBJDZLCBCHYXYZHZFYWXYZYMSDBZZYJGTSMTFXQYXQSTDGSLNXDLRYZZLRYYLXQHT");
    listStrJP.append("XSRTZNGZXBNQQZFMYKMZJBZYMKBPNLYZPBLMCNQYZZZSJZHJCTZKHYZZJRDYZHNPXGLFZTLKGJTCTSSYLLGZRZBBQZZKLPKLCZYS");
    listStrJP.append("SUYXBJFPNJZZXCDWXZYJXZZDJJKGGRSRJKMSMZJLSJYWQSKYHQJSXPJZZZLSNSHRNYPZTWCHKLPSRZLZXYJQXQKYSJYCZTLQZYBB");
    listStrJP.append("YBWZPQDWWYZCYTJCJXCKCWDKKZXSGKDZXWWYYJQYYTCYTDLLXWKCZKKLCCLZCQQDZLQLCSFQCHQHSFSMQZZLNBJJZBSJHTSZDYSJ");
    listStrJP.append("QJPDLZCDCWJKJZZLPYCGMZWDJJBSJQZSYZYHHXJPBJYDSSXDZNCGLQMBTSFSBPDZDLZNFGFJGFSMPXJQLMBLGQCYYXBQKDJJQYRF");
    listStrJP.append("KZTJDHCZKLBSDZCFJTPLLJGXHYXZCSSZZXSTJYGKGCKGYOQXJPLZPBPGTGYJZGHZQZZLBJLSQFZGKQQJZGYCZBZQTLDXRJXBSXXP");
    listStrJP.append("ZXHYZYCLWDXJJHXMFDZPFZHQHQMQGKSLYHTYCGFRZGNQXCLPDLBZCSCZQLLJBLHBZCYPZZPPDYMZZSGYHCKCPZJGSLJLNSCDSLDL");
    listStrJP.append("XBMSTLDDFJMKDJDHZLZXLSZQPQPGJLLYBDSZGQLBZLSLKYYHZTTNTJYQTZZPSZQZTLLJTYYLLQLLQYZQLBDZLSLYYZYMDFSZSNHL");
    listStrJP.append("XZNCZQZPBWSKRFBSYZMTHBLGJPMCZZLSTLXSHTCSYZLZBLFEQHLXFLCJLYLJQCBZLZJHHSSTBRMHXZHJZCLXFNBGXGTQJCZTMSFZ");
    listStrJP.append("KJMSSNXLJKBHSJXNTNLZDNTLMSJXGZJYJCZXYJYJWRWWQNZTNFJSZPZSHZJFYRDJSFSZJZBJFZQZZHZLXFYSBZQLZSGYFTZDCSZX");
    listStrJP.append("ZJBQMSZKJRHYJZCKMJKHCHGTXKXQGLXPXFXTRTYLXJXHDTSJXHJZJXZWZLCQSBTXWXGXTXXHXFTSDKFJHZYJFJXRZSDLLLTQSQQZ");
    listStrJP.append("QWZXSYQTWGWBZCGZLLYZBCLMQQTZHZXZXLJFRMYZFLXYSQXXJKXRMQDZDMMYYBSQBHGZMWFWXGMXLZPYYTGZYCCDXYZXYWGSYJYZ");
    listStrJP.append("NBHPZJSQSYXSXRTFYZGRHZTXSZZTHCBFCLSYXZLZQMZLMPLMXZJXSFLBYZMYQHXJSXRXSQZZZSSLYFRCZJRCRXHHZXQYDYHXSJJH");
    listStrJP.append("ZCXZBTYNSYSXJBQLPXZQPYMLXZKYXLXCJLCYSXXZZLXDLLLJJYHZXGYJWKJRWYHCPSGNRZLFZWFZZNSXGXFLZSXZZZBFCSYJDBRJ");
    listStrJP.append("KRDHHGXJLJJTGXJXXSTJTJXLYXQFCSGSWMSBCTLQZZWLZZKXJMLTMJYHSDDBXGZHDLBMYJFRZFSGCLYJBPMLYSMSXLSZJQQHJZFX");
    listStrJP.append("GFQFQBPXZGYYQXGZTCQWYLTLGWSGWHRLFSFGZJMGMGBGTJFSYZZGZYZAFLSSPMLPFLCWBJZCLJJMZLPJJLYMQDMYYYFBGYGYZMLY");
    listStrJP.append("ZDXQYXRQQQHSYYYQXYLJTYXFSFSLLGNQCYHYCWFHCCCFXPYLYPLLZYXXXXXKQHHXSHJZCFZSCZJXCPZWHHHHHAPYLQALPQAFYHXD");
    listStrJP.append("YLUKMZQGGGDDESRNNZLTZGCHYPPYSQJJHCLLJTOLNJPZLJLHYMHEYDYDSQYCDDHGZUNDZCLZYZLLZNTNYZGSLHSLPJJBDGWXPCDU");
    listStrJP.append("TJCKLKCLWKLLCASSTKZZDNQNTTLYYZSSYSSZZRYLJQKCQDHHCRXRZYDGRGCWCGZQFFFPPJFZYNAKRGYWYQPQXXFKJTSZZXSWZDDF");
    listStrJP.append("BBXTBGTZKZNPZZPZXZPJSZBMQHKCYXYLDKLJNYPKYGHGDZJXXEAHPNZKZTZCMXCXMMJXNKSZQNMNLWBWWXJKYHCPSTMCSQTZJYXT");
    listStrJP.append("PCTPDTNNPGLLLZSJLSPBLPLQHDTNJNLYYRSZFFJFQWDPHZDWMRZCCLODAXNSSNYZRESTYJWJYJDBCFXNMWTTBYLWSTSZGYBLJPXG");
    listStrJP.append("LBOCLHPCBJLTMXZLJYLZXCLTPNCLCKXTPZJSWCYXSFYSZDKNTLBYJCYJLLSTGQCBXRYZXBXKLYLHZLQZLNZCXWJZLJZJNCJHXMNZ");
    listStrJP.append("ZGJZZXTZJXYCYYCXXJYYXJJXSSSJSTSSTTPPGQTCSXWZDCSYFPTFBFHFBBLZJCLZZDBXGCXLQPXKFZFLSYLTUWBMQJHSZBMDDBCY");
    listStrJP.append("SCCLDXYCDDQLYJJWMQLLCSGLJJSYFPYYCCYLTJANTJJPWYCMMGQYYSXDXQMZHSZXPFTWWZQSWQRFKJLZJQQYFBRXJHHFWJJZYQAZ");
    listStrJP.append("MYFRHCYYBYQWLPEXCCZSTYRLTTDMQLYKMBBGMYYJPRKZNPBSXYXBHYZDJDNGHPMFSGMWFZMFQMMBCMZZCJJLCNUXYQLMLRYGQZCY");
    listStrJP.append("XZLWJGCJCGGMCJNFYZZJHYCPRRCMTZQZXHFQGTJXCCJEAQCRJYHPLQLSZDJRBCQHQDYRHYLYXJSYMHZYDWLDFRYHBPYDTSSCNWBX");
    listStrJP.append("GLPZMLZZTQSSCPJMXXYCSJYTYCGHYCJWYRXXLFEMWJNMKLLSWTXHYYYNCMMCWJDQDJZGLLJWJRKHPZGGFLCCSCZMCBLTBHBQJXQD");
    listStrJP.append("SPDJZZGKGLFQYWBZYZJLTSTDHQHCTCBCHFLQMPWDSHYYTQWCNZZJTLBYMBPDYYYXSQKXWYYFLXXNCWCXYPMAELYKKJMZZZBRXYYQ");
    listStrJP.append("JFLJPFHHHYTZZXSGQQMHSPGDZQWBWPJHZJDYSCQWZKTXXSQLZYYMYSDZGRXCKKUJLWPYSYSCSYZLRMLQSYLJXBCXTLWDQZPCYCYK");
    listStrJP.append("PPPNSXFYZJJRCEMHSZMSXLXGLRWGCSTLRSXBZGBZGZTCPLUJLSLYLYMTXMTZPALZXPXJTJWTCYYZLBLXBZLQMYLXPGHDSLSSDMXM");
    listStrJP.append("BDZZSXWHAMLCZCPJMCNHJYSNSYGCHSKQMZZQDLLKABLWJXSFMOCDXJRRLYQZKJMYBYQLYHETFJZFRFKSRYXFJTWDSXXSYSQJYSLY");
    listStrJP.append("XWJHSNLXYYXHBHAWHHJZXWMYLJCSSLKYDZTXBZSYFDXGXZJKHSXXYBSSXDPYNZWRPTQZCZENYGCXQFJYKJBZMLJCMQQXUOXSLYXX");
    listStrJP.append("LYLLJDZBTYMHPFSTTQQWLHOKYBLZZALZXQLHZWRRQHLSTMYPYXJJXMQSJFNBXYXYJXXYQYLTHYLQYFMLKLJTMLLHSZWKZHLJMLHL");
    listStrJP.append("JKLJSTLQXYLMBHHLNLZXQJHXCFXXLHYHJJGBYZZKBXSCQDJQDSUJZYYHZHHMGSXCSYMXFEBCQWWRBPYYJQTYZCYQYQQZYHMWFFHG");
    listStrJP.append("ZFRJFCDPXNTQYZPDYKHJLFRZXPPXZDBBGZQSTLGDGYLCQMLCHHMFYWLZYXKJLYPQHSYWMQQGQZMLZJNSQXJQSYJYCBEHSXFSZPXZ");
    listStrJP.append("WFLLBCYYJDYTDTHWZSFJMQQYJLMQXXLLDTTKHHYBFPWTYYSQQWNQWLGWDEBZWCMYGCULKJXTMXMYJSXHYBRWFYMWFRXYQMXYSZTZ");
    listStrJP.append("ZTFYKMLDHQDXWYYNLCRYJBLPSXCXYWLSPRRJWXHQYPHTYDNXHHMMYWYTZCSQMTSSCCDALWZTCPQPYJLLQZYJSWXMZZMMYLMXCLMX");
    listStrJP.append("CZMXMZSQTZPPQQBLPGXQZHFLJJHYTJSRXWZXSCCDLXTYJDCQJXSLQYCLZXLZZXMXQRJMHRHZJBHMFLJLMLCLQNLDXZLLLPYPSYJY");
    listStrJP.append("SXCQQDCMQJZZXHNPNXZMEKMXHYKYQLXSXTXJYYHWDCWDZHQYYBGYBCYSCFGPSJNZDYZZJZXRZRQJJYMCANYRJTLDPPYZBSTJKXXZ");
    listStrJP.append("YPFDWFGZZRPYMTNGXZQBYXNBUFNQKRJQZMJEGRZGYCLKXZDSKKNSXKCLJSPJYYZLQQJYBZSSQLLLKJXTBKTYLCCDDBLSPPFYLGYD");
    listStrJP.append("TZJYQGGKQTTFZXBDKTYYHYBBFYTYYBCLPDYTGDHRYRNJSPTCSNYJQHKLLLZSLYDXXWBCJQSPXBPJZJCJDZFFXXBRMLAZHCSNDLBJ");
    listStrJP.append("DSZBLPRZTSWSBXBCLLXXLZDJZSJPYLYXXYFTFFFBHJJXGBYXJPMMMPSSJZJMTLYZJXSWXTYLEDQPJMYGQZJGDJLQJWJQLLSJGJGY");
    listStrJP.append("GMSCLJJXDTYGJQJQJCJZCJGDZZSXQGSJGGCXHQXSNQLZZBXHSGZXCXYLJXYXYYDFQQJHJFXDHCTXJYRXYSQTJXYEFYYSSYYJXNCY");
    listStrJP.append("ZXFXMSYSZXYYSCHSHXZZZGZZZGFJDLTYLNPZGYJYZYYQZPBXQBDZTZCZYXXYHHSQXSHDHGQHJHGYWSZTMZMLHYXGEBTYLZKQWYTJ");
    listStrJP.append("ZRCLEKYSTDBCYKQQSAYXCJXWWGSBHJYZYDHCSJKQCXSWXFLTYNYZPZCCZJQTZWJQDZZZQZLJJXLSBHPYXXPSXSHHEZTXFPTLQYZZ");
    listStrJP.append("XHYTXNCFZYYHXGNXMYWXTZSJPTHHGYMXMXQZXTSBCZYJYXXTYYZYPCQLMMSZMJZZLLZXGXZAAJZYXJMZXWDXZSXZDZXLEYJJZQBH");
    listStrJP.append("ZWZZZQTZPSXZTDSXJJJZNYAZPHXYYSRNQDTHZHYYKYJHDZXZLSWCLYBZYECWCYCRYLCXNHZYDZYDYJDFRJJHTRSQTXYXJRJHOJYN");
    listStrJP.append("XELXSFSFJZGHPZSXZSZDZCQZBYYKLSGSJHCZSHDGQGXYZGXCHXZJWYQWGYHKSSEQZZNDZFKWYSSTCLZSTSYMCDHJXXYWEYXCZAYD");
    listStrJP.append("MPXMDSXYBSQMJMZJMTZQLPJYQZCGQHXJHHLXXHLHDLDJQCLDWBSXFZZYYSCHTYTYYBHECXHYKGJPXHHYZJFXHWHBDZFYZBCAPNPG");
    listStrJP.append("NYDMSXHMMMMAMYNBYJTMPXYYMCTHJBZYFCGTYHWPHFTWZZEZSBZEGPFMTSKFTYCMHFLLHGPZJXZJGZJYXZSBBQSCZZLZCCSTPGXM");
    listStrJP.append("JSFTCCZJZDJXCYBZLFCJSYZFGSZLYBCWZZBYZDZYPSWYJZXZBDSYUXLZZBZFYGCZXBZHZFTPBGZGEJBSTGKDMFHYZZJHZLLZZGJQ");
    listStrJP.append("ZLSFDJSSCBZGPDLFZFZSZYZYZSYGCXSNXXCHCZXTZZLJFZGQSQYXZJQDCCZTQCDXZJYQJQCHXZTDLGSCXZSYQJQTZWLQDQZTQCHQ");
    listStrJP.append("QJZYEZZZPBWKDJFCJPZTYPQYQTTYNLMBDKTJZPQZQZZFPZSBNJLGYJDXJDZZKZGQKXDLPZJTCJDQBXDJQJSTCKNXBXZMSLYJCQMT");
    listStrJP.append("JQWWCJQNJNLLLHJCWQTBZQYDZCZPZZDZYDDCYZZZCCJTTJFZDPRRTZTJDCQTQZDTJNPLZBCLLCTZSXKJZQZPZLBZRBTJDCXFCZDB");
    listStrJP.append("CCJJLTQQPLDCGZDBBZJCQDCJWYNLLZYZCCDWLLXWZLXRXNTQQCZXKQLSGDFQTDDGLRLAJJTKUYMKQLLTZYTDYYCZGJWYXDXFRSKS");
    listStrJP.append("TQTENQMRKQZHHQKDLDAZFKYPBGGPZREBZZYKZZSPEGJXGYKQZZZSLYSYYYZWFQZYLZZLZHWCHKYPQGNPGBLPLRRJYXCCSYYHSFZF");
    listStrJP.append("YBZYYTGZXYLXCZWXXZJZBLFFLGSKHYJZEYJHLPLLLLCZGXDRZELRHGKLZZYHZLYQSZZJZQLJZFLNBHGWLCZCFJYSPYXZLZLXGCCP");
    listStrJP.append("ZBLLCYBBBBUBBCBPCRNNZCZYRBFSRLDCGQYYQXYGMQZWTZYTYJXYFWTEHZZJYWLCCNTZYJJZDEDPZDZTSYQJHDYMBJNYJZLXTSST");
    listStrJP.append("PHNDJXXBYXQTZQDDTJTDYYTGWSCSZQFLSHLGLBCZPHDLYZJYCKWTYTYLBNYTSDSYCCTYSZYYEBHEXHQDTWNYGYCLXTSZYSTQMYGZ");
    listStrJP.append("AZCCSZZDSLZCLZRQXYYELJSBYMXSXZTEMBBLLYYLLYTDQYSHYMRQWKFKBFXNXSBYCHXBWJYHTQBPBSBWDZYLKGZSKYHXQZJXHXJX");
    listStrJP.append("GNLJKZLYYCDXLFYFGHLJGJYBXQLYBXQPQGZTZPLNCYPXDJYQYDYMRBESJYYHKXXSTMXRCZZYWXYQYBMCLLYZHQYZWQXDBXBZWZMS");
    listStrJP.append("LPDMYSKFMZKLZCYQYCZLQXFZZYDQZPZYGYJYZMZXDZFYFYTTQTZHGSPCZMLCCYTZXJCYTJMKSLPZHYSNZLLYTPZCTZZCKTXDHXXT");
    listStrJP.append("QCYFKSMQCCYYAZHTJPCYLZLYJBJXTPNYLJYYNRXSYLMMNXJSMYBCSYSYLZYLXJJQYLDZLPQBFZZBLFNDXQKCZFYWHGQMRDSXYCYT");
    listStrJP.append("XNQQJZYYPFZXDYZFPRXEJDGYQBXRCNFYYQPGHYJDYZXGRHTKYLNWDZNTSMPKLBTHBPYSZBZTJZSZZJTYYXZPHSSZZBZCZPTQFZMY");
    listStrJP.append("FLYPYBBJQXZMXXDJMTSYSKKBJZXHJCKLPSMKYJZCXTMLJYXRZZQSLXXQPYZXMKYXXXJCLJPRMYYGADYSKQLSNDHYZKQXZYZTCGHZ");
    listStrJP.append("TLMLWZYBWSYCTBHJHJFCWZTXWYTKZLXQSHLYJZJXTMPLPYCGLTBZZTLZJCYJGDTCLKLPLLQPJMZPAPXYZLKKTKDZCZZBNZDYDYQZ");
    listStrJP.append("JYJGMCTXLTGXSZLMLHBGLKFWNWZHDXUHLFMKYSLGXDTWWFRJEJZTZHYDXYKSHWFZCQSHKTMQQHTZHYMJDJSKHXZJZBZZXYMPAGQM");
    listStrJP.append("STPXLSKLZYNWRTSQLSZBPSPSGZWYHTLKSSSWHZZLYYTNXJGMJSZSUFWNLSOZTXGXLSAMMLBWLDSZYLAKQCQCTMYCFJBSLXCLZZCL");
    listStrJP.append("XXKSBZQCLHJPSQPLSXXCKSLNHPSFQQYTXYJZLQLDXZQJZDYYDJNZPTUZDSKJFSLJHYLZSQZLBTXYDGTQFDBYAZXDZHZJNHHQBYKN");
    listStrJP.append("XJJQCZMLLJZKSPLDYCLBBLXKLELXJLBQYCXJXGCNLCQPLZLZYJTZLJGYZDZPLTQCSXFDMNYCXGBTJDCZNBGBQYQJWGKFHTNPYQZQ");
    listStrJP.append("GBKPBBYZMTJDYTBLSQMPSXTBNPDXKLEMYYCJYNZCTLDYKZZXDDXHQSHDGMZSJYCCTAYRZLPYLTLKXSLZCGGEXCLFXLKJRTLQJAQZ");
    listStrJP.append("NCMBYDKKCXGLCZJZXJHPTDJJMZQYKQSECQZDSHHADMLZFMMZBGNTJNNLGBYJBRBTMLBYJDZXLCJLPLDLPCQDHLXZLYCBLCXZZJAD");
    listStrJP.append("JLNZMMSSSMYBHBSQKBHRSXXJMXSDZNZPXLGBRHWGGFCXGMSKLLTSJYYCQLTSKYWYYHYWXBXQYWPYWYKQLSQPTNTKHQCWDQKTWPXX");
    listStrJP.append("HCPTHTWUMSSYHBWCRWXHJMKMZNGWTMLKFGHKJYLSYYCXWHYECLQHKQHTTQKHFZLDXQWYZYYDESBPKYRZPJFYYZJCEQDZZDLATZBB");
    listStrJP.append("FJLLCXDLMJSSXEGYGSJQXCWBXSSZPDYZCXDNYXPPZYDLYJCZPLTXLSXYZYRXCYYYDYLWWNZSAHJSYQYHGYWWAXTJZDAXYSRLTDPS");
    listStrJP.append("SYYFNEJDXYZHLXLLLZQZSJNYQYQQXYJGHZGZCYJCHZLYCDSHWSHJZYJXCLLNXZJJYYXNFXMWFPYLCYLLABWDDHWDXJMCXZTZPMLQ");
    listStrJP.append("ZHSFHZYNZTLLDYWLSLXHYMMYLMBWWKYXYADTXYLLDJPYBPWUXJMWMLLSAFDLLYFLBHHHBQQLTZJCQJLDJTFFKMMMBYTHYGDCQRDD");
    listStrJP.append("WRQJXNBYSNWZDBYYTBJHPYBYTTJXAAHGQDQTMYSTQXKBTZPKJLZRBEQQSSMJJBDJOTGTBXPGBKTLHQXJJJCTHXQDWJLWRFWQGWSH");
    listStrJP.append("CKRYSWGFTGYGBXSDWDWRFHWYTJJXXXJYZYSLPYYYPAYXHYDQKXSHXYXGSKQHYWFDDDPPLCJLQQEEWXKSYYKDYPLTJTHKJLTCYYHH");
    listStrJP.append("JTTPLTZZCDLTHQKZXQYSTEEYWYYZYXXYYSTTJKLLPZMCYHQGXYHSRMBXPLLNQYDQHXSXXWGDQBSHYLLPJJJTHYJKYPPTHYYKTYEZ");
    listStrJP.append("YENMDSHLCRPQFDGFXZPSFTLJXXJBSWYYSKSFLXLPPLBBBLBSFXFYZBSJSSYLPBBFFFFSSCJDSTZSXZRYYSYFFSYZYZBJTBCTSBSD");
    listStrJP.append("HRTJJBYTCXYJEYLXCBNEBJDSYXYKGSJZBXBYTFZWGENYHHTHZHHXFWGCSTBGXKLSXYWMTMBYXJSTZSCDYQRCYTWXZFHMYMCXLZNS");
    listStrJP.append("DJTTTXRYCFYJSBSDYERXJLJXBBDEYNJGHXGCKGSCYMBLXJMSZNSKGXFBNBPTHFJAAFXYXFPXMYPQDTZCXZZPXRSYWZDLYBBKTYQP");
    listStrJP.append("QJPZYPZJZNJPZJLZZFYSBTTSLMPTZRTDXQSJEHBZYLZDHLJSQMLHTXTJECXSLZZSPKTLZKQQYFSYGYWPCPQFHQHYTQXZKRSGTTSQ");
    listStrJP.append("CZLPTXCDYYZXSQZSLXLZMYCPCQBZYXHBSXLZDLTCDXTYLZJYYZPZYZLTXJSJXHLPMYTXCQRBLZSSFJZZTNJYTXMYJHLHPPLCYXQJ");
    listStrJP.append("QQKZZSCPZKSWALQSBLCCZJSXGWWWYGYKTJBBZTDKHXHKGTGPBKQYSLPXPJCKBMLLXDZSTBKLGGQKQLSBKKTFXRMDKBFTPZFRTBBR");
    listStrJP.append("FERQGXYJPZSSTLBZTPSZQZSJDHLJQLZBPMSMMSXLQQNHKNBLRDDNXXDHDDJCYYGYLXGZLXSYGMQQGKHBPMXYXLYTQWLWGCPBMQXC");
    listStrJP.append("YZYDRJBHTDJYHQSHTMJSBYPLWHLZFFNYPMHXXHPLTBQPFBJWQDBYGPNZTPFZJGSDDTQSHZEAWZZYLLTYYBWJKXXGHLFKXDJTMSZS");
    listStrJP.append("QYNZGGSWQSPHTLSSKMCLZXYSZQZXNCJDQGZDLFNYKLJCJLLZLMZZNHYDSSHTHZZLZZBBHQZWWYCRZHLYQQJBEYFXXXWHSRXWQHWP");
    listStrJP.append("SLMSSKZTTYGYQQWRSLALHMJTQJSMXQBJJZJXZYZKXBYQXBJXSHZTSFJLXMXZXFGHKZSZGGYLCLSARJYHSLLLMZXELGLXYDJYTLFB");
    listStrJP.append("HBPNLYZFBBHPTGJKWETZHKJJXZXXGLLJLSTGSHJJYQLQZFKCGNNDJSSZFDBCTWWSEQFHQJBSAQTGYPQLBXBMMYWXGSLZHGLZGQYF");
    listStrJP.append("LZBYFZJFRYSFMBYZHQGFWZSYFYJJPHZBYYZFFWODGRLMFTWLBZGYCQXCDJYGZYYYYTYTYDWEGAZYHXJLZYYHLRMGRXXZCLHNELJJ");
    listStrJP.append("TJTPWJYBJJBXJJTJTEEKHWSLJPLPSFYZPQQBDLQJJTYYQLYZKDKSQJYYQZLDQTGJQYZJSUCMRYQTHTEJMFCTYHYPKMHYZWJDQFHY");
    listStrJP.append("YXWSHCTXRLJHQXHCCYYYJLTKTTYTMXGTCJTZAYYOCZLYLBSZYWJYTSJYHBYSHFJLYGJXXTMZYYLTXXYPZLXYJZYZYYPNHMYMDYYL");
    listStrJP.append("BLHLSYYQQLLNJJYMSOYQBZGDLYXYLCQYXTSZEGXHZGLHWBLJHEYXTWQMAKBPQCGYSHHEGQCMWYYWLJYJHYYZLLJJYLHZYHMGSLJL");
    listStrJP.append("JXCJJYCLYCJPCPZJZJMMYLCQLNQLJQJSXYJMLSZLJQLYCMMHCFMMFPQQMFYLQMCFFQMMMMHMZNFHHJGTTHHKHSLNCHHYQDXTMMQD");
    listStrJP.append("CYZYXYQMYQYLTDCYYYZAZZCYMZYDLZFFFMMYCQZWZZMABTBYZTDMNZZGGDFTYPCGQYTTSSFFWFDTZQSSYSTWXJHXYTSXXYLBYQHW");
    listStrJP.append("WKXHZXWZNNZZJZJJQJCCCHYYXBZXZCYZTLLCQXYNJYCYYCYNZZQYYYEWYCZDCJYCCHYJLBTZYYCQWMPWPYMLGKDLDLGKQQBGYCHJ");
    listStrJP.append("XY");
}

std::string ZhToPY::zhToPY(const std::string &chinese)
{
    if (listPY.size() == 0) {
        return "";
    }

    std::string listStr;
    std::vector<std::string> words = split_name(chinese);
    for (auto const &w : words) {
        int unicode = get_code_point(w);
        if (unicode >= 0x4E00 && unicode <= 0x9FA5) {
            //这里的listPY就是按照UNICODE每个中文对应的拼音数组
            listStr.append(listPY.at(unicode - 0x4E00));
        } else {
            listStr.append(w);
        }
    }

    return listStr;
}

std::string ZhToPY::zhToJP(const std::string &chinese)
{
    std::string strChineseFirstPY = listStrJP;
    if(chinese.length() == 0) {
        return chinese;
    }

    std::vector<std::string> words = split_name(chinese);
    std::string str;
    int index = 0;
    for(auto const &w : words) {
        //若是字母或数字则直接输出
        ushort vChar = get_code_point(w) ;
        if((vChar >= 'a' && vChar <= 'z' ) || (vChar >= 'A' && vChar <= 'Z')) {
            str.append(w);
        }

        if((vChar >= '0' && vChar <= '9')) {
            str.append(w);
        } else {
            index = (int)vChar - 19968;
            if(index >= 0 && index < strChineseFirstPY.length()) {
                std::string tmpStr;
                tmpStr.push_back(strChineseFirstPY.at(index));
                str.append(tmpStr);
            }
        }
    }

    return str;
}

std::string ZhToPY::zhToZM(const std::string &chinese)
{
    std::string tmpStr;
    tmpStr.push_back(zhToJP(chinese).at(0));
    return tmpStr;
}

#endif // ZHTOPY_H
