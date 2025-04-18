
public class TextFormatter {
    public static String formatText(String text) {
        int lengthStr = text.length();
        StringBuilder sb = new StringBuilder(text);
        for (int i = 1; i < lengthStr; i++) {
            if (Character.isWhitespace(sb.charAt(i)) && Character.isWhitespace(sb.charAt(i - 1))) {
                sb.deleteCharAt(i - 1);
                lengthStr--;
                i--;
            }
            if (!(Character.isWhitespace(sb.charAt(i)) || Character.isLetterOrDigit(sb.charAt(i)))) {
                if (Character.isWhitespace(sb.charAt(i - 1))) {
                    sb.deleteCharAt(i - 1);
                    lengthStr--;
                    i--;
                }
            }

        }
        sb.insert(0, "  ");
        lengthStr += 2;
        boolean found = false;
        for (int i = 1; i <= lengthStr / 80; i++) {
            if (!(Character.isWhitespace(sb.charAt((i * 80))))) {
                for (int j = i * 80; !(found); j-- ) {
                    if (Character.isWhitespace(sb.charAt((j)))) {
                        sb.insert(j, "\n");
                        sb.deleteCharAt(j + 1);
                        found = true;
                    }
                      
                }
            } else {
                sb.insert(i * 80, "\n");
                sb.deleteCharAt((i * 80) + 1);
                
                
            }
        }
        
        String result = sb.toString();
        return result;
    }
}

