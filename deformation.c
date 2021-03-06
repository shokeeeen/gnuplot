#include <stdio.h>
#include <stdlib.h>

int main()
{
  float beta2;
  
  printf("beta2?\n");
  scanf("%f",&beta2);
  
  FILE *gp;// For gnuplot
  
  // gnuplotの起動コマンドgp = _popen("gnuplot.exe", "w")) == NULL) {	// gnuplotをパイプで起動
  gp = popen("gnuplot -persist", "w");
  
  // --- gnuplotにコマンドを送る --- //
  fprintf(gp,"set parametric\n");
  fprintf(gp,"set angle degree\n");
  fprintf(gp,"set isosample 16,16\n");
  fprintf(gp,"set ticslevel 0\n");
  fprintf(gp,"set view 75,25\n");
  fprintf(gp,"set size 0.7,1.0\n");
  fprintf(gp,"set xrange [-2:2]\n");
  fprintf(gp,"set yrange [-2:2]\n");
  fprintf(gp,"set zrange [-2:2]\n");
  fprintf(gp,"set urange [0:360]\n");
  fprintf(gp,"set vrange [0:360]\n");
  fprintf(gp,"y0(t)=1.0\n");
  fprintf(gp,"y2(t)=sqrt(5.0/(4*pi))*(3.0*sin(t)**2-1.0)/2.0\n");
  fprintf(gp,"b2=%f\n",beta2);
  fprintf(gp,"r(t)=y0(t)+b2*y2(t)\n");
  //  fprintf(gp,"r(t)=b2*y2(0.5*pi-t)\n");
  fprintf(gp,"fx(u,v)=cos(u)*cos(v)\n");
  fprintf(gp,"fy(u,v)=sin(u)*cos(v)\n");
  fprintf(gp,"fz(v)=sin(v)\n");
  fprintf(gp,"set pm3d\n");
  fprintf(gp,"splot r(v)*fx(u,v),r(v)*fy(u,v),r(v)*fz(v) with lines\n");
  
  fflush(gp); // バッファに格納されているデータを吐き出す（必須）
  system("pause");
  fprintf(gp, "exit\n"); // gnuplotの終了
  pclose(gp);
}
