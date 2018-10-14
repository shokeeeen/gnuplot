#include <stdio.h>
#include <stdlib.h>

int main()
{
  float epsilon,a,b,aob;
  
  printf("epsilon?\n");
  scanf("%f",&epsilon);

  a   = 1 + epsilon;
  b   = 1 - epsilon/2;
  aob = a/b;
  printf("a/b = %f\n", aob);
  
  FILE *gp;// For gnuplot
  
  // gnuplotの起動コマンドgp = _popen("gnuplot.exe", "w")) == NULL) {	// gnuplotをパイプで起動
  gp = popen("gnuplot -persist", "w");
  
  /* --- gnuplotにコマンドを送る --- */
  fprintf(gp,"set parametric\n");
  fprintf(gp,"set angle degree\n");
  fprintf(gp,"set isosample 16,16\n"); //the number of lines
  fprintf(gp,"set ticslevel 0\n");
  fprintf(gp,"set view 75,25\n");
  fprintf(gp,"set size 0.7,1.0\n");
  fprintf(gp,"set xrange [-2:2]\n");
  fprintf(gp,"set yrange [-2:2]\n");
  fprintf(gp,"set zrange [-2:2]\n");
  fprintf(gp,"set urange [0:360]\n");
  fprintf(gp,"set vrange [0:360]\n");
  fprintf(gp,"eps=%f\n",epsilon);
  fprintf(gp,"a=1+eps\n");
  fprintf(gp,"b=1-eps/2\n");
  fprintf(gp,"z(t)=a*sin(t)\n");
  fprintf(gp,"x(t)=b*cos(t)\n");
  fprintf(gp,"r(t)=sqrt(x(t)*x(t)+z(t)*z(t))\n");
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
