import org.antlr.v4.runtime.*;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;

public class SimpleLexTest {
    public static TreeMap<Integer, ArrayList<String>>  tokenCat;
    public static void main(String [] args) {
        tokenCat = new TreeMap<Integer,ArrayList<String>>();
        String fileName = "test.txt";
        ANTLRInputStream stream = null;
        try {
            stream = new ANTLRInputStream(new FileInputStream(fileName));
        } catch (IOException e) {
            e.printStackTrace();
        }
        SimpleLex lexer = new SimpleLex(stream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        tokens.fill();
        for (int i = 0; i < tokens.size(); i++)
        {
            Token tok = tokens.get(i);
            if( ! tokenCat.containsKey(tok.getType()) ) {
                tokenCat.put(tok.getType(), new ArrayList<String>());
            }
            tokenCat.get(tok.getType()).add(tok.getText());
            //System.out.printf("%-5d: %s\n", tok.getType(), tok.getText());
        }

        for( Map.Entry<Integer, ArrayList<String>> entry : tokenCat.entrySet() ) {
            System.out.printf("%d : ", entry.getKey());
            for( String s : entry.getValue() ) {
                System.out.printf("%s, ", s);
            }
            System.out.println();
        }

    }
}
