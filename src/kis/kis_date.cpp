//---------------------------------------------------------------------------
//
// "華和梨" for あれ以外の何か以外の何か
// KawariInlineScript -- 日時 --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.14  Phase 0.50    First version
//  2001.05.19  Phase 5.1     少し強化
//  2001.06.17  Phase 6.0     もう少し強化
//  2001.08.08  Phase 6.2     ostrstreamバグ修正
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_date.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <ctime>
#include <strstream>
#include <iomanip>
using namespace std;
//---------------------------------------------------------------------------
string KIS_date::Function(const vector<string>& args)
{
	time_t nowtt=time(NULL);
	struct tm *now=localtime(&nowtt);

	string format="%y/%m/%d %H:%M:%S";
	if(args.size()>=2) format=args[1];

	ostrstream ret;
	format+=' ';	// ダミー
	for(unsigned int i=0;i<(format.size()-1);i++) {
		if(format[i]=='%') {
			i++;
			switch(format[i]) {
			case 'd':	// 日 (01..31)
				ret << setw(2) << setfill('0') << now->tm_mday;
				break;
			case 'e':	// 日 (1..31)
				ret << now->tm_mday;
				break;
			case 'H':	// 時 (00..23)
				ret << setw(2) << setfill('0') << now->tm_hour;
				break;
			case 'j':	// 元日からの通算日 (001..366)
				ret << setw(3) << setfill('0') << (now->tm_yday+1);
				break;
			case 'J':	// 元日からの通算日 (1..366)
				ret << (now->tm_yday+1);
				break;
			case 'k':	// 時 (0..23)
				ret << now->tm_hour;
				break;
			case 'm':	// 月 (01..12)
				ret << setw(2) << setfill('0') << (now->tm_mon+1);
				break;
			case 'M':	// 分 (00..59)
				ret << setw(2) << setfill('0') << now->tm_min;
				break;
			case 'n':	// 月 (1..12)
				ret << (now->tm_mon+1);
				break;
			case 'N':	// 分 (0..59)
				ret << now->tm_min;
				break;
			case 'r':	// 秒 (0..59)
				ret << now->tm_sec;
				break;
			case 'S':	// 秒 (00..59)
				ret << setw(2) << setfill('0') << now->tm_sec;
				break;
			case 'w':	// 曜日 (0..6) 日曜日が0
				ret << now->tm_wday;
				break;
			case 'y':	// 年 (2000...) 4桁
			case 'Y':	// 年 (2000...) 4桁
				ret << (now->tm_year+1900);
				break;
			case '%':
				ret << '%';
				break;
			default:
				ret << '%';
				i--;
			}
		} else {
			ret << format[i];
		}
	}
	ret << ends;

	string retstr(ret.str());
	ret.freeze(false);

	return(retstr);
}
//---------------------------------------------------------------------------

