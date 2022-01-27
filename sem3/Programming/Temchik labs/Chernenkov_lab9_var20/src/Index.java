import java.io.*;
import java.util.*;
import java.util.zip.*;

class KeyComp implements Comparator<String> {
    public int compare(String o1, String o2) {
        return o1.compareTo(o2);
    }
}

class KeyCompReverse implements Comparator<String> {
    public int compare(String o1, String o2) {
        return o2.compareTo(o1);
    }
}

interface IndexBase {
    String[] getKeys(Comparator<String> comp);

    void put(String key, long value);

    boolean contains(String key);

    Vector<Long> get(String key);
}

class IndexOne2One implements Serializable, IndexBase {
    private static final long serialVersionUID = 1L;

    private HashMap<String, Long> map;

    public IndexOne2One() {
        map = new HashMap<String, Long>();
    }

    public String[] getKeys(Comparator<String> comp) {
        String[] result = map.keySet().toArray(new String[0]);
        Arrays.sort(result, comp);
        return result;
    }

    public void put(String key, long value) {
        map.put(key, new Long(value));
    }

    public boolean contains(String key) {
        return map.containsKey(key);
    }

    public Vector<Long> get(String key) {
        long pos = map.get(key).longValue();
        Vector<Long> a = new Vector<Long>(1);
        a.add(0, pos);
        return a;
    }
}

class IndexOne2N implements Serializable, IndexBase {
    private static final long serialVersionUID = 1L;

    private HashMap<String, Vector<Long>> map;

    public IndexOne2N() {
        map = new HashMap<String, Vector<Long>>();
    }

    public String[] getKeys(Comparator<String> comp) {
        String[] result = map.keySet().toArray(new String[0]);
        Arrays.sort(result, comp);
        return result;
    }

    public void put(String key, long value) {
        Vector<Long> arr = map.get(key);
        arr = Index.InsertValue(arr, value);
        map.put(key, arr);
    }

    public void put(String keys,
                    String keyDel,
                    long value) {
        StringTokenizer st = new StringTokenizer(keys, keyDel);
        int num = st.countTokens();
        for (int i = 0; i < num; i++) {
            String key = st.nextToken();
            key = key.trim();
            put(key, value);
        }
    }

    public boolean contains(String key) {
        return map.containsKey(key);
    }

    public Vector<Long> get(String key) {
        return map.get(key);
    }
}

class KeyNotUniqueException extends Exception {
    private static final long serialVersionUID = 1L;

    public KeyNotUniqueException(String key) {
        super(new String("Key is not unique: " + key));
    }
}

public class Index implements Serializable, Closeable {
    private static final long serialVersionUID = 1L;

    public static Vector<Long> InsertValue(Vector<Long> arr, long value) {

        if (arr == null)
            arr = new Vector<Long>();
        arr.addElement(new Long(value));

        return arr;
    }

    IndexOne2One          number;
    IndexOne2N            surname;
    IndexOne2N            adress;
	
    public void test( Phone phone ) throws KeyNotUniqueException {
        assert( phone != null );
        if ( number.contains(phone.number)) {
            throw new KeyNotUniqueException( phone.number );
        }	
    }
	
    public void put( Phone phone, long value ) throws KeyNotUniqueException {
        test( phone );
        number.put( phone.number, value );
        surname.put( phone.surname, value);
        adress.put( phone.adress, value);		
    }
	
    public Index()  {
        number   = new IndexOne2One();
        surname = new IndexOne2N();
        adress 	= new IndexOne2N();
    }
	
    public static Index load( String name ) 
            throws IOException, ClassNotFoundException {
        Index obj = null;
        try {
            FileInputStream file = new FileInputStream( name );
            try( ZipInputStream zis = new ZipInputStream( file )) {
                ZipEntry zen = zis.getNextEntry();
                if ( zen.getName().equals( Buffer.zipEntryName )== false ) {
                    throw new IOException("Invalid block format");
                }
                try ( ObjectInputStream ois = new ObjectInputStream( zis )) {
                    obj = (Index) ois.readObject();
                }
            }
        } catch ( FileNotFoundException e ) {
            obj = new Index();
        }
        if ( obj != null ) {
            obj.save( name );
        }
        return obj;
    }
	
    private transient String filename = null; 
	
    public void save( String name ) {
        filename = name;
    }
	
    public void saveAs( String name ) throws IOException {
        FileOutputStream file = new FileOutputStream( name );
        try ( ZipOutputStream zos = new ZipOutputStream( file )) {
            zos.putNextEntry( new ZipEntry( Buffer.zipEntryName ));
            zos.setLevel( ZipOutputStream.DEFLATED );
            try ( ObjectOutputStream oos = new ObjectOutputStream( zos )) {
                oos.writeObject( this );
                oos.flush();
                zos.closeEntry();
                zos.flush();
            }
        }
    }
	
    public void close() throws IOException {
        saveAs( filename );
    }
}
