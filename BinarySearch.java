public class BinarySearch {
    
    
    static void search(int[] array, int num){
        int hi = array.length - 1;
        int lo = 0;
        int mid;
        boolean found = false;
        while(lo <= hi){
            mid = (hi+lo)/2;
            if(array[mid] == num){
                System.out.println("FOUND " + num);
                found = true;
                break;
            } else {
                if(array[mid] < num){
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
        }
        if(!found){
            System.out.println("NOT FOUND " + num);
        }
    }

    public static void main(String[] args){
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        search(array, 1);
        search(array, 2);
        search(array, 3);
        search(array, 4);
        search(array, 5);
        search(array, 6);
        search(array, 7);
        search(array, 8);
        search(array, 9);
        search(array, 0);
        search(array, -1);
        search(array, 12);
    }

}