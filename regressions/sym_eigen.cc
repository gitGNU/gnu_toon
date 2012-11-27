#undef TOON_CHECK_BOUNDS
#define TOON_CHECK_BOUNDS
#undef TOON_INITIALIZE_SNAN
#define TOON_INITIALIZE_NAN


#include <TooN/SymEigen.h>
#include "regressions/regression.h"
#include <iomanip>
#include <algorithm>

using namespace TooN;
using namespace std;

template<int Size, int Size2>
void test_(const Matrix<Size>& m)
{
	Matrix<Size2> M = m;
	SymEigen<Size2> e(M);
	cout << setprecision(15);
	cout << e.get_evectors() << endl;
	cout << e.get_evalues() << endl;
	cout << endl << endl;
}

template<int Size>
void test(const Matrix<Size>& m)
{
	test_<Size, Size>(m);
	test_<Size, Dynamic>(m);
}



template<int Size1>
void test_things_(int S2, int & sorted, double & n)
{
	Matrix<Size1> m = Zeros(S2);
	
	for(int r=0; r < m.num_rows(); r++)
		for(int c=r; c < m.num_cols(); c++)
			m[r][c] = m[c][r] = xor128d();

	SymEigen<Size1> sm(m);

	//Check the results are sorted low to high
	for(int i=1; i < m.num_rows(); i++)
		if(sm.get_evalues()[i-1] > sm.get_evalues()[i])
		{
			sorted++;
			break;
		}
	
	//Check that  Mx = lX

	n = max(n, norm_inf(m * sm.get_evectors()[0] - sm.get_evalues()[0] * sm.get_evectors()[0]));
}


void test_things()
{
	int s=0;
	double e=0;
	for(int n=0; n < 200; n++)
	{
		test_things_<2>(2, s, e);
		test_things_<3>(3, s, e);
		test_things_<4>(4, s, e);
		test_things_<5>(5, s, e);
		test_things_<6>(6, s, e);
		test_things_<7>(7, s, e);
		test_things_<8>(8, s, e);
		test_things_<9>(9, s, e);

		test_things_<Dynamic>(2, s, e);
		test_things_<Dynamic>(3, s, e);
		test_things_<Dynamic>(4, s, e);
		test_things_<Dynamic>(5, s, e);
		test_things_<Dynamic>(6, s, e);
		test_things_<Dynamic>(7, s, e);
		test_things_<Dynamic>(8, s, e);
		test_things_<Dynamic>(9, s, e);


		test_things_<Dynamic>(n+9, s, e);
	}

	cout << "Sorted " << s << endl;
	cout << "Errors " << e << endl;

}


int main()
{
	
	test_things();

	test<3>(Data(0, 0, 0,
	             0, 1, 1,
	             0, 1, 2));

	//Size 2 (special case)
	test<2>(Data(
		  -1,  0,
		   0, -2));

	test<3>(Data(
		  -1,  0,  0,
		   0, -2,  0, 
		   0,  0, -3));

	test<4>(Data(
		  -1,  0,  0, 0,
		   0, -2,  0, 0,
		   0,  0, -3, 0,
		   0,  0,  0, -4));

test<2>(Data(2.687284882248026e-01,1.611208355913847e+00,1.611208355913847e+00,5.101380514788435e-01));
test<2>(Data(9.908701741838820e-01,1.101084037511501e+00,1.101084037511501e+00,1.577446702271026e+00));
test<2>(Data(1.877191735484699e-01,8.641125804418760e-01,8.641125804418760e-01,8.655341358101069e-01));
test<2>(Data(1.524560164915884e+00,4.474932474059122e-01,4.474932474059122e-01,1.443080064681565e+00));
test<2>(Data(4.575244425409054e-01,1.846698153165406e+00,1.846698153165406e+00,6.117996606710716e-02));
test<2>(Data(5.089172198692169e-02,1.480561635572007e+00,1.480561635572007e+00,7.624084753764250e-01));
test<2>(Data(4.331987942612269e-01,4.511573631575854e-01,4.511573631575854e-01,4.433833325460702e-01));
test<2>(Data(8.757751873011442e-01,7.288966916394234e-01,7.288966916394234e-01,4.617330830819687e-01));
test<2>(Data(4.375620746753773e-01,7.493850803282193e-01,7.493850803282193e-01,4.297941053181784e-02));
test<2>(Data(1.675155951325146e+00,1.198748685584879e+00,1.198748685584879e+00,3.718125317894355e-01));
test<3>(Data(1.985086824352130e+00,1.192641714155419e+00,1.057330546605266e+00,1.192641714155419e+00,1.442968815166537e+00,1.133298769656695e+00,1.057330546605266e+00,1.133298769656695e+00,1.660071386548654e+00));
test<3>(Data(1.340611132828142e+00,1.185847511764775e+00,1.176582864126111e+00,1.185847511764775e+00,1.692394836856626e+00,5.398096507309420e-01,1.176582864126111e+00,5.398096507309420e-01,4.854799470861354e-01));
test<3>(Data(1.594808495108606e+00,9.631127606889274e-01,5.477104220806913e-01,9.631127606889274e-01,1.406081524131263e+00,1.113447460546890e+00,5.477104220806913e-01,1.113447460546890e+00,1.016852976499964e+00));
test<3>(Data(1.556885230000292e+00,1.010631938075403e+00,1.096637183568062e+00,1.010631938075403e+00,5.914992793381422e-02,1.026675007666201e+00,1.096637183568062e+00,1.026675007666201e+00,1.186367460760115e+00));
test<3>(Data(7.871993727558281e-01,1.152425834394216e+00,1.362528337354033e+00,1.152425834394216e+00,1.541046279661601e+00,7.717935765127935e-01,1.362528337354033e+00,7.717935765127935e-01,1.027543326375274e+00));
test<3>(Data(1.904934776536539e+00,8.470742852426243e-01,4.648408613610614e-01,8.470742852426243e-01,1.095992618932498e+00,1.740771514075617e+00,4.648408613610614e-01,1.740771514075617e+00,1.640971823850964e+00));
test<3>(Data(1.772359161652016e+00,1.259181695356198e+00,8.652631983932200e-01,1.259181695356198e+00,1.122715729556758e+00,1.296100834864790e+00,8.652631983932200e-01,1.296100834864790e+00,1.139998667752760e+00));
test<3>(Data(3.996788403542862e-01,8.615104319738192e-01,1.108414565025239e+00,8.615104319738192e-01,6.921558380363099e-01,1.150931260520570e+00,1.108414565025239e+00,1.150931260520570e+00,9.162936001994489e-01));
test<3>(Data(5.594996816768481e-02,8.140659020554653e-01,9.743088215740789e-01,8.140659020554653e-01,1.722017721706650e+00,1.614876311138117e+00,9.743088215740789e-01,1.614876311138117e+00,5.105880801746120e-01));
test<3>(Data(1.683489664548192e+00,6.898041555542667e-01,3.327933634573208e-01,6.898041555542667e-01,2.911994984962472e-02,8.650754025465576e-01,3.327933634573208e-01,8.650754025465576e-01,1.249604168304953e+00));
test<4>(Data(6.888457281929899e-01,2.376603247532757e-01,4.816272910811735e-01,9.482990782570888e-01,2.376603247532757e-01,5.458288736373603e-01,1.185360941355552e+00,6.427409347969769e-01,4.816272910811735e-01,1.185360941355552e+00,4.726915526397422e-02,4.953187972068833e-01,9.482990782570888e-01,6.427409347969769e-01,4.953187972068833e-01,1.799637000712040e+00));
test<4>(Data(1.020231961857353e+00,2.299091010610576e-01,7.658762326637212e-01,1.037639416400564e+00,2.299091010610576e-01,3.572904165559074e-02,8.510673682513485e-01,1.694429990579673e+00,7.658762326637212e-01,8.510673682513485e-01,1.356351590553895e+00,1.342513021285055e+00,1.037639416400564e+00,1.694429990579673e+00,1.342513021285055e+00,1.033199033898786e+00));
test<4>(Data(4.463915604933416e-01,9.697522274443817e-01,1.362801320009189e+00,8.862095901411908e-01,9.697522274443817e-01,1.261895722542694e+00,9.343193604416505e-01,1.237894381758296e+00,1.362801320009189e+00,9.343193604416505e-01,6.127732406664920e-01,1.602356525023680e+00,8.862095901411908e-01,1.237894381758296e+00,1.602356525023680e+00,8.323445255300511e-01));
test<4>(Data(5.047162045596708e-01,8.278943730764661e-01,1.746498962643840e+00,4.158853649421888e-01,8.278943730764661e-01,1.924402250361636e+00,1.544055806404872e+00,5.184479797403404e-01,1.746498962643840e+00,1.544055806404872e+00,1.408046284660143e+00,7.146355033725953e-01,4.158853649421888e-01,5.184479797403404e-01,7.146355033725953e-01,1.348306028493728e+00));
test<4>(Data(8.659002422006327e-01,4.901913180683413e-01,1.004102492476296e+00,1.653007246206709e+00,4.901913180683413e-01,9.995998444736033e-01,3.434386385164682e-01,1.654321883152931e+00,1.004102492476296e+00,3.434386385164682e-01,4.017060228815189e-01,6.668363529472013e-01,1.653007246206709e+00,1.654321883152931e+00,6.668363529472013e-01,4.260595927616276e-01));
test<4>(Data(1.348910139447526e+00,1.720094272620428e+00,1.166827906764666e+00,1.254837598298888e+00,1.720094272620428e+00,1.374220364307315e+00,1.209963908853767e+00,1.198476424817222e+00,1.166827906764666e+00,1.209963908853767e+00,1.693604608329685e-01,9.288103245108279e-01,1.254837598298888e+00,1.198476424817222e+00,9.288103245108279e-01,1.200417660264499e+00));
test<4>(Data(1.682264391411710e+00,1.235527822992552e+00,4.756312123974411e-01,3.644087062434833e-01,1.235527822992552e+00,1.207965057783422e+00,1.505477931241406e+00,1.753433462083535e+00,4.756312123974411e-01,1.505477931241406e+00,2.085499960292273e-01,8.272542473221369e-01,3.644087062434833e-01,1.753433462083535e+00,8.272542473221369e-01,1.657011942938227e+00));
test<4>(Data(6.817949282331669e-01,1.185967558158060e+00,1.672671729488060e+00,6.552223949460858e-01,1.185967558158060e+00,4.474281454975385e-01,6.461900955925911e-01,1.053738306542065e+00,1.672671729488060e+00,6.461900955925911e-01,1.850134404216947e+00,1.285537415686975e+00,6.552223949460858e-01,1.053738306542065e+00,1.285537415686975e+00,2.476348897333334e-02));
test<4>(Data(1.340823278047862e+00,1.317066595066826e-01,2.306606790202007e-01,9.878942163659709e-01,1.317066595066826e-01,4.792667297350187e-01,1.155541936067364e+00,1.331778005709601e+00,2.306606790202007e-01,1.155541936067364e+00,4.828405701956863e-01,1.122283687081234e+00,9.878942163659709e-01,1.331778005709601e+00,1.122283687081234e+00,1.940528073056421e+00));
test<4>(Data(1.818445456301423e+00,3.941527288989999e-01,1.235993762591590e+00,7.902909570411959e-01,3.941527288989999e-01,1.304100398978834e+00,3.351700734626224e-01,7.347094156631770e-02,1.235993762591590e+00,3.351700734626224e-01,1.193141286376883e+00,1.363236551796038e+00,7.902909570411959e-01,7.347094156631770e-02,1.363236551796038e+00,1.939626553676231e+00));
test<5>(Data(1.939593008992940e+00,6.542755076116075e-01,5.225143878486120e-01,1.065709120544851e+00,1.286737180741591e+00,6.542755076116075e-01,1.376379616095425e+00,9.082156249604416e-01,9.110965263663156e-01,8.688436776000987e-01,5.225143878486120e-01,9.082156249604416e-01,1.627375307675757e-01,9.242528038345172e-01,1.300111864105005e+00,1.065709120544851e+00,9.110965263663156e-01,9.242528038345172e-01,1.881469044498000e+00,1.237613316965138e+00,1.286737180741591e+00,8.688436776000987e-01,1.300111864105005e+00,1.237613316965138e+00,1.787000491043202e+00));
test<5>(Data(6.056186593450327e-01,5.794314095460106e-01,6.151417817217186e-01,1.072246479067222e+00,6.730695262649204e-01,5.794314095460106e-01,4.074805689250480e-02,3.188890920824389e-01,9.349765116511203e-01,1.500432703888442e+00,6.151417817217186e-01,3.188890920824389e-01,1.270764187126114e+00,4.450011465822398e-01,9.654268662538961e-01,1.072246479067222e+00,9.349765116511203e-01,4.450011465822398e-01,1.002859171893387e+00,1.571192476731960e+00,6.730695262649204e-01,1.500432703888442e+00,9.654268662538961e-01,1.571192476731960e+00,1.969791742288145e+00));
test<5>(Data(1.643100289487029e+00,6.132734971636735e-01,4.229464123424428e-01,1.260543136459771e+00,1.634181391179499e+00,6.132734971636735e-01,1.787517595391580e+00,1.044768930740807e+00,1.600076853692999e+00,6.995386855828787e-01,4.229464123424428e-01,1.044768930740807e+00,1.607712561967944e+00,1.085308632641121e+00,1.093304930040621e+00,1.260543136459771e+00,1.600076853692999e+00,1.085308632641121e+00,8.652760019524740e-01,2.223111370998220e-01,1.634181391179499e+00,6.995386855828787e-01,1.093304930040621e+00,2.223111370998220e-01,1.926771766643151e+00));
test<5>(Data(1.616505256744793e+00,9.449803761132867e-01,9.580615342833907e-01,9.764216816168703e-01,1.065754600615157e+00,9.449803761132867e-01,6.773382897901178e-01,8.285727240494942e-01,2.835214717409323e-01,8.799684972959469e-01,9.580615342833907e-01,8.285727240494942e-01,1.246432616070422e-01,1.183877824671454e+00,1.457612869972322e-01,9.764216816168703e-01,2.835214717409323e-01,1.183877824671454e+00,7.955946261297456e-01,9.297838918076147e-01,1.065754600615157e+00,8.799684972959469e-01,1.457612869972322e-01,9.297838918076147e-01,1.001799239114453e+00));
test<5>(Data(1.297679184681707e+00,9.333892063577268e-01,1.593452635164049e+00,8.029733373889689e-01,1.121384244537570e+00,9.333892063577268e-01,9.576537751635869e-01,1.142768668876989e+00,9.239378421175475e-01,8.722094663232913e-01,1.593452635164049e+00,1.142768668876989e+00,5.504507269315982e-01,1.523839254589076e+00,7.407543079642184e-01,8.029733373889689e-01,9.239378421175475e-01,1.523839254589076e+00,3.189354615156622e-01,1.615018981283887e+00,1.121384244537570e+00,8.722094663232913e-01,7.407543079642184e-01,1.615018981283887e+00,7.432286614951299e-01));
test<5>(Data(1.402565325815617e+00,1.696496933540177e+00,1.164095154438696e+00,1.204258646869812e+00,1.877825429264508e+00,1.696496933540177e+00,1.142465388435091e+00,9.340260098729121e-01,7.656512131707212e-01,1.025562421954253e+00,1.164095154438696e+00,9.340260098729121e-01,1.042664422843730e-01,8.464346076386431e-01,1.345601765349651e+00,1.204258646869812e+00,7.656512131707212e-01,8.464346076386431e-01,1.459792300973997e+00,3.082349319836607e-01,1.877825429264508e+00,1.025562421954253e+00,1.345601765349651e+00,3.082349319836607e-01,1.825725780184864e+00));
test<5>(Data(1.918877675754143e+00,8.395339254382015e-01,1.578468781116072e+00,1.750815618446228e+00,7.778073873157717e-01,8.395339254382015e-01,8.901174642290234e-01,1.357229394005464e+00,1.930631608240425e+00,6.778288276319916e-01,1.578468781116072e+00,1.357229394005464e+00,3.295084373665477e-01,4.446540092631389e-01,3.745464459154907e-01,1.750815618446228e+00,1.930631608240425e+00,4.446540092631389e-01,1.201358162374117e+00,1.157800908898340e+00,7.778073873157717e-01,6.778288276319916e-01,3.745464459154907e-01,1.157800908898340e+00,8.017911908091957e-03));
test<5>(Data(3.796774078661674e-01,1.274105421002801e+00,6.067727564888302e-01,1.601142698087327e+00,1.176172167965539e+00,1.274105421002801e+00,4.132116313703694e-01,5.356638430115981e-01,1.087716434578617e+00,6.564820819791958e-01,6.067727564888302e-01,5.356638430115981e-01,1.367054305171915e+00,1.281899998197016e+00,1.092702065897367e+00,1.601142698087327e+00,1.087716434578617e+00,1.281899998197016e+00,1.711395399597287e+00,8.772065945935473e-01,1.176172167965539e+00,6.564820819791958e-01,1.092702065897367e+00,8.772065945935473e-01,1.615098178746561e+00));
test<5>(Data(2.361430610613312e-01,1.720785019268097e+00,1.048319577974643e+00,1.414497472525587e+00,1.253364792744898e+00,1.720785019268097e+00,2.731880258796152e-01,8.571902374352325e-01,8.773774753866661e-01,9.589196991546567e-01,1.048319577974643e+00,8.571902374352325e-01,1.056787942702887e+00,4.002474655454302e-01,8.198725439634420e-01,1.414497472525587e+00,8.773774753866661e-01,4.002474655454302e-01,1.566174622343982e+00,8.873269343994827e-01,1.253364792744898e+00,9.589196991546567e-01,8.198725439634420e-01,8.873269343994827e-01,7.751315755111543e-03));
test<5>(Data(5.552425032188438e-01,1.585182343763088e+00,1.869254624293378e+00,1.188843281973684e+00,1.372205516848743e+00,1.585182343763088e+00,9.231619477396068e-01,1.139930078534815e+00,4.124845833780225e-01,1.329058644820864e+00,1.869254624293378e+00,1.139930078534815e+00,3.406256504265687e-01,1.009196350337465e+00,1.264786972827202e+00,1.188843281973684e+00,4.124845833780225e-01,1.009196350337465e+00,8.517389442073203e-01,1.303161243375429e+00,1.372205516848743e+00,1.329058644820864e+00,1.264786972827202e+00,1.303161243375429e+00,1.497546927150275e+00));
test<6>(Data(9.854041038100939e-01,1.375030371574434e+00,1.455681262486292e+00,1.192992192466221e+00,1.139956281478751e+00,9.141625719631343e-01,1.375030371574434e+00,1.267465021891255e+00,1.542580354269188e+00,9.345436523283233e-01,1.591015732055808e+00,1.713626885675192e+00,1.455681262486292e+00,1.542580354269188e+00,6.989001767733675e-01,1.097558543515565e+00,1.130617838210569e+00,1.564389666751667e+00,1.192992192466221e+00,9.345436523283233e-01,1.097558543515565e+00,9.690861578229354e-01,8.222799418667358e-01,4.473117881029319e-01,1.139956281478751e+00,1.591015732055808e+00,1.130617838210569e+00,8.222799418667358e-01,1.313687077797704e+00,7.086496236915464e-01,9.141625719631343e-01,1.713626885675192e+00,1.564389666751667e+00,4.473117881029319e-01,7.086496236915464e-01,1.209987838631917e+00));
test<6>(Data(4.177787829651355e-01,7.309060983063167e-01,1.599462288098870e+00,4.414321821345253e-01,7.815750907616501e-01,1.262443213488635e+00,7.309060983063167e-01,7.364163319459055e-01,1.326522366061011e+00,1.526493313232542e+00,1.012346230132255e+00,1.414659991737551e+00,1.599462288098870e+00,1.326522366061011e+00,5.395212673522768e-01,1.476384195314694e+00,2.626483533109071e-01,1.346456629550510e+00,4.414321821345253e-01,1.526493313232542e+00,1.476384195314694e+00,6.592871206410572e-01,1.121711873465768e+00,1.153689285237264e+00,7.815750907616501e-01,1.012346230132255e+00,2.626483533109071e-01,1.121711873465768e+00,1.244904121795273e+00,9.424156595790476e-01,1.262443213488635e+00,1.414659991737551e+00,1.346456629550510e+00,1.153689285237264e+00,9.424156595790476e-01,3.312590550043154e-01));
test<6>(Data(1.946099662470022e+00,9.701688792107175e-01,1.153638609117045e+00,1.220609345114130e+00,8.228176953552302e-01,6.044271969967835e-01,9.701688792107175e-01,2.772394832739716e-01,8.562561355535638e-01,8.157239809334441e-01,3.958032042102687e-01,1.589244929517287e+00,1.153638609117045e+00,8.562561355535638e-01,1.436953852793555e+00,4.922571414202965e-01,8.103090282988242e-01,5.150749604002565e-01,1.220609345114130e+00,8.157239809334441e-01,4.922571414202965e-01,1.106861056309610e-01,1.412424130344729e+00,1.581513061561543e+00,8.228176953552302e-01,3.958032042102687e-01,8.103090282988242e-01,1.412424130344729e+00,1.928243173467779e+00,7.084098060753384e-01,6.044271969967835e-01,1.589244929517287e+00,5.150749604002565e-01,1.581513061561543e+00,7.084098060753384e-01,7.994114940347977e-01));
test<6>(Data(9.900457628043579e-01,9.578270177558510e-01,1.162990987690468e+00,8.119710722785607e-01,1.733829917863744e+00,5.925546633194234e-01,9.578270177558510e-01,4.238140352323191e-01,7.611530070996787e-01,1.248957490117976e+00,6.087996400759921e-01,1.372376336649072e+00,1.162990987690468e+00,7.611530070996787e-01,1.594885423857382e+00,1.257516418698924e+00,4.647526872540805e-01,1.223127969736719e+00,8.119710722785607e-01,1.248957490117976e+00,1.257516418698924e+00,1.760060337546824e+00,1.423371741090863e+00,1.058357431055412e+00,1.733829917863744e+00,6.087996400759921e-01,4.647526872540805e-01,1.423371741090863e+00,1.142393732777850e-01,4.149595259960687e-01,5.925546633194234e-01,1.372376336649072e+00,1.223127969736719e+00,1.058357431055412e+00,4.149595259960687e-01,1.217035133377292e-01));
test<6>(Data(1.681248070730645e+00,6.803277959204640e-01,9.046532887873564e-01,7.079322159870449e-01,4.442652593332287e-01,7.411693391707319e-01,6.803277959204640e-01,1.489228535879713e+00,1.656366184927379e+00,1.195237514528635e+00,1.075666211438244e+00,1.132984987947849e+00,9.046532887873564e-01,1.656366184927379e+00,1.283206666046505e+00,8.484444837531611e-01,2.595524363187953e-01,1.656281290652794e+00,7.079322159870449e-01,1.195237514528635e+00,8.484444837531611e-01,1.120515192126947e+00,1.402277004015053e+00,8.130131436685561e-01,4.442652593332287e-01,1.075666211438244e+00,2.595524363187953e-01,1.402277004015053e+00,8.482395547616589e-01,9.139663595532090e-01,7.411693391707319e-01,1.132984987947849e+00,1.656281290652794e+00,8.130131436685561e-01,9.139663595532090e-01,1.952807353385793e+00));
test<6>(Data(3.020195075677202e-01,1.731703197331623e+00,1.297918551358270e+00,1.376673849783057e+00,7.854174293438340e-01,3.949625567079564e-01,1.731703197331623e+00,9.383336529303760e-01,4.984563141666034e-01,1.075064067264616e+00,3.533246283370877e-01,9.562954148245784e-01,1.297918551358270e+00,4.984563141666034e-01,7.903765255719749e-01,1.508040861965537e+00,1.012320508855456e+00,2.700097057175970e-01,1.376673849783057e+00,1.075064067264616e+00,1.508040861965537e+00,1.715705588734092e-01,8.287655431023101e-01,9.414136950937948e-01,7.854174293438340e-01,3.533246283370877e-01,1.012320508855456e+00,8.287655431023101e-01,1.613838763790370e+00,1.185966965562320e+00,3.949625567079564e-01,9.562954148245784e-01,2.700097057175970e-01,9.414136950937948e-01,1.185966965562320e+00,6.773266719180365e-01));
test<6>(Data(1.567242836819473e+00,1.944326717066535e+00,1.415757383944767e+00,4.500672165758181e-01,9.508959139397790e-01,5.973682168189969e-01,1.944326717066535e+00,1.438762990295974e+00,1.126111994121538e+00,1.276191924400192e+00,8.882351465742122e-01,1.811236394245852e+00,1.415757383944767e+00,1.126111994121538e+00,3.140637904401750e-01,4.139264873395463e-01,8.463663687777288e-01,4.229530185029624e-01,4.500672165758181e-01,1.276191924400192e+00,4.139264873395463e-01,1.629897353037659e+00,1.399630822642031e+00,6.412146239779757e-01,9.508959139397790e-01,8.882351465742122e-01,8.463663687777288e-01,1.399630822642031e+00,1.002113714942505e+00,5.949745369976590e-01,5.973682168189969e-01,1.811236394245852e+00,4.229530185029624e-01,6.412146239779757e-01,5.949745369976590e-01,1.958823163503591e+00));
test<6>(Data(9.593956836185179e-01,1.835174060934281e+00,1.711565792463736e+00,1.372326751708358e+00,1.502871484389261e+00,9.755482590936007e-01,1.835174060934281e+00,1.602735356332371e+00,8.374974326976390e-01,9.882832995834494e-01,1.138379543919168e+00,1.091719934571643e+00,1.711565792463736e+00,8.374974326976390e-01,1.493298073688877e+00,1.341332691394209e+00,1.849119819027721e+00,1.189208791043249e+00,1.372326751708358e+00,9.882832995834494e-01,1.341332691394209e+00,1.064256794863076e+00,3.523978799238592e-01,4.140842107294748e-01,1.502871484389261e+00,1.138379543919168e+00,1.849119819027721e+00,3.523978799238592e-01,8.222176274537402e-01,8.348978148702458e-01,9.755482590936007e-01,1.091719934571643e+00,1.189208791043249e+00,4.140842107294748e-01,8.348978148702458e-01,5.233951369937245e-01));
test<6>(Data(1.264282175469642e+00,6.997446950711939e-01,3.622491663328203e-01,7.484117832882142e-01,1.848786944103862e+00,1.130314774175558e+00,6.997446950711939e-01,1.723668134690669e+00,9.131308778430866e-01,9.125811071145220e-01,1.104190922483678e+00,1.114021483237272e+00,3.622491663328203e-01,9.131308778430866e-01,1.196156002485981e+00,1.810228557047883e+00,1.094157004680496e+00,1.308141007738278e+00,7.484117832882142e-01,9.125811071145220e-01,1.810228557047883e+00,1.596321485670778e+00,1.472601313923906e+00,1.610264252268397e+00,1.848786944103862e+00,1.104190922483678e+00,1.094157004680496e+00,1.472601313923906e+00,1.540665021251389e+00,1.098881395918645e+00,1.130314774175558e+00,1.114021483237272e+00,1.308141007738278e+00,1.610264252268397e+00,1.098881395918645e+00,8.023816871384190e-02));
test<6>(Data(1.702283188520101e+00,5.784983249624531e-01,7.617287557893517e-01,7.076550446358687e-01,1.241328942884413e+00,5.714155925588476e-01,5.784983249624531e-01,6.053072737528674e-01,1.438568161997491e+00,1.376825682048585e+00,1.947371428840764e+00,9.113918920302084e-01,7.617287557893517e-01,1.438568161997491e+00,1.051254427603433e+00,8.497999786745636e-01,9.815387888217955e-01,1.355507618184534e+00,7.076550446358687e-01,1.376825682048585e+00,8.497999786745636e-01,6.038207729301405e-01,1.142981763584831e+00,1.522790750856093e+00,1.241328942884413e+00,1.947371428840764e+00,9.815387888217955e-01,1.142981763584831e+00,1.989062017562657e+00,1.631465736125124e+00,5.714155925588476e-01,9.113918920302084e-01,1.355507618184534e+00,1.522790750856093e+00,1.631465736125124e+00,1.339352578197877e+00));

}
