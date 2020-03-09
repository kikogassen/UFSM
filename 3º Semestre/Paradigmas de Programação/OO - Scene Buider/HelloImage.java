import java.util.ArrayList;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;

public class HelloImage extends Application {
    
    int id = 0;
    ArrayList<Image> lista = new ArrayList<Image>();
    
   public static void main(String[] args) {
      launch(args);
   }
   
    @Override
    public void start(Stage stage) {
        HBox pane = new HBox();
        pane.setAlignment(Pos.CENTER);
        lista.add(new Image("acacia.png"));
        lista.add(new Image("carvalho.png"));
        lista.add(new Image("carvalhoescuro.png"));
        lista.add(new Image("eucalipto.png"));
        lista.add(new Image("pinheiro.png"));
        lista.add(new Image("selva.png"));
        //imageView.setPreserveRatio(true);
        //imageView.setFitWidth(150);
        ImageView iv = new ImageView(lista.get(id));
        Button btLeft = new Button();
        Button btRight = new Button();
        btLeft.setText("<");
        btRight.setText(">");
        btLeft.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
                id = id==0 ? 5 : id-1;
                iv.setImage(lista.get(id));
            }
        });
        btRight.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
                id = id==5 ? 0 : id+1;
                iv.setImage(lista.get(id));
            }
        });
        pane.getChildren().addAll(btLeft, iv, btRight);
        stage.setScene(new Scene(pane, 300, 250));
        stage.show();
    }
}
