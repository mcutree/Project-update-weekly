unsigned char  TempBuffer0[17]={0x54,0x48,0x3a,0x2b,0x31,0x32,0x35,0x20,
								0x54,0x4c,0x3a,0x2b,0x31,0x32,0x34,0x43,'\0'};
								//显示温度上下限,上电时显示TH:+125 TL:+124C	
void covert0( char TH, char TL)	//将温度上下限转换为LCD显示的数据
{ 
   if(TH>0x7F)                    //判断正负,如果为负温,将其转化为其绝对值
   {
    TempBuffer0[3]=0x2d;	     //0x2d为"-"的ASCII码
	TH=~TH+1;
   }
   else TempBuffer0[0]=0x2b;	//0x2B为"+"的ASCII码

   if(TL>0x7f)
   {
   TempBuffer0[11]=0x2d;	     //0x2d为"-"的ASCII码
   TL=~TL+1;
   }
   else TempBuffer0[11]=0x2b;	//0x2B为"+"的ASCII码

  TempBuffer0[4]=TH/100+0x30;		             //分离出TH的百十个位
  if( TempBuffer0[4]==0x30) TempBuffer0[4]=0xfe; //百位数消隐
  TempBuffer0[5]=(TH%100)/10+0x30;				//分离出十位
  TempBuffer0[6]=(TH%100)%10+0x30;	 			//分离出个位
  TempBuffer0[12]=TH/100+0x30;		             //分离出TL的百十个位
  if( TempBuffer0[12]==0x30) TempBuffer0[12]=0xfe; //百位数消隐
  TempBuffer0[13]=(TH%100)/10+0x30;				//分离出十位
  TempBuffer0[14]=(TH%100)%10+0x30;	 			//分离出个位

