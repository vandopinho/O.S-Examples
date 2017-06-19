
package exercicio.medias;
import java.util.Random;


public class Monitores {
    public static void main(String[] args) {
        float[] nota = new float [] {0, 0, 0, 0, 0, 0};
        Random gerador = new Random();
        float faltas = gerador.nextInt(37);
        for(int i=0; i<6; i++){
            nota[i] = gerador.nextInt(11);
        }
        soma(nota,faltas);
    }
    private static synchronized void soma(float[] nota, float faltas){
        float somaNota = 0;
        for(int i=0; i<6; i++){
            somaNota += nota[i];
        }
        faltas = (float) (faltas * 0.03);
        somaNota = somaNota - faltas;
        System.out.println(somaNota);
    }
}
