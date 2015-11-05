//Is s2 a rotation of s1, assuming we can make a call to a function isSubstring that returns true if a string is a substring of another?
//NON FUNCTIONAL, NO isSubString method present.

public boolean isRotation(String s1, String s2){
    if(s1.length() == s2.length() && s1.length() > 0 ){
        String s1s1 = s1 + s1;
        return isSubString(s1s1, s2);
    }
    return false;
}