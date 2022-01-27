package t22;

/*
 * ���������� ����� ������.
 * ����������� ������ ��� ������������ 
 * 									   ������ �������
 *                                     ���������� ������������
 *                                     ��������
 *                                     ���������
 *                                     ��������� �� ���������
 * */
public class Vector3D {
public double x, y, z;	//���������� �������
    
    /**
     * ����������� ������. ������������� �������.
     */
    public Vector3D()
    {
        this.x = this.y = this.z =0;
    }
    
    /**
     * ����������� ������. ������������� �������.
     * @param x - ���������� �
     * @param y - ���������� y
     * @param z - ���������� z
     * @return void;
     */
    public Vector3D(double x, double y, double z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    
    public Vector3D(Vector3D v) {
    	x = v.x;
    	y = v.y;
    	z = v.z;
    }
    
    /**
     * ��������� ���� ��������
     * @param vec
     * @return ��������� ���������
     */
    public Vector3D sub(Vector3D vec)
    {
        Vector3D res = new Vector3D(
        		this.x - vec.x,
        		this.y - vec.y,
        		this.z - vec.z);
        return res;
    }
    
    /**
     * �������� ���� ��������
     * @param vec
     * @return ��������� ��������
     */
    public Vector3D add(Vector3D vec)
    {
        Vector3D res = new Vector3D(
        		this.x + vec.x,
        		this.y + vec.y,
        		this.z + vec.z);
        return res;
    }
    
    /**
     * ��������� ������� �� ���������
     * @param con - ���������
     * @return - ��������� ���������
     */
    public Vector3D mul(double con)
    {
        Vector3D res = new Vector3D(
        		this.x * con, 
        		this.y * con, 
        		this.z * con);
        return res;
    }
    
    /**
     * ������� ������� �� ���������
     * @param con - ���������
     * @return - ��������� �������
     */
    public Vector3D div(double con)
    {
        Vector3D res = new Vector3D(
        		this.x / con,
        		this.y / con,
        		this.z / con);
        return res;
    }
    
    /**
     * ��������� ������������ ���� ��������
     * @param vec
     * @return - ��������� ���������� ������������
     */
    public Vector3D cross(Vector3D vec)
    {
        Vector3D res = new Vector3D(
        		(this.y * vec.z) - (this.z * vec.y),
        		(this.z * vec.x) - (this.x * vec.z),
        		(this.x * vec.y) - (this.y * vec.x));
        return res;
    }
    
    /**
     * ������ �������
     * ����� �������
     * @return - ����� �������
     */
    public double length()
    {
        return Math.sqrt((this.x * this.x) + 
        		(this.y * this.y) + 
        		(this.z * this.z));
    }
    
    /**
     * ������������ �������
     * @return - ��������� ������
     */
    public Vector3D normalize()
    {
    	double magnitude = this.length();				
    	Vector3D res = new Vector3D();
    	double coef = 1/magnitude;
    	res = this.mul(coef);
    	return res;
    }
    
    /**
     * ��������� ������������ ���� ��������
     * @param vec
     */
    public double dot(Vector3D vec)
    {
        return this.x*vec.x + this.y*vec.y + this.z*vec.z;
    }
    
    /**
     * @return ���������� �
     */
    public double getX()
    {
        return this.x;
    }

    /**
     * @return ���������� y
     */
    public double getY()
    {
        return this.y;
    }
 
    /**
     * @return ���������� z
     */    
    public double getZ()
    {
        return this.z;
    }
    
    public String toString()
    {
    	return x + "i + " + y + "j + " + z + "k";
    }
    
    private boolean eq(double a, double b) {
    	return Math.abs(a - b) < 1e-8;
    }
    
    public boolean isOrtogonal(Vector3D v) {
    	return eq(dot(v), 0.00000000);
    }
    
    public boolean isCollinear(Vector3D v) {
    	return eq(cross(v).length(), 0.00000000);
    }
}
