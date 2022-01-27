package t22;

/*
 * Определить класс вектор.
 * Реализовать методы для вычислениния 
 * 									   модуля вектора
 *                                     скалярного произведения
 *                                     сложения
 *                                     вычитания
 *                                     умножения на константу
 * */
public class Vector3D {
public double x, y, z;	//Координаты вектора
    
    /**
     * Конструктор класса. Инициализация вектора.
     */
    public Vector3D()
    {
        this.x = this.y = this.z =0;
    }
    
    /**
     * Конструктор класса. Инициализация вектора.
     * @param x - координата х
     * @param y - координата y
     * @param z - координата z
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
     * Вычитание двух векторов
     * @param vec
     * @return результат вычитания
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
     * Сложение двух векторов
     * @param vec
     * @return результат сложения
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
     * Умножение вектора на константу
     * @param con - константа
     * @return - результат умножения
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
     * Деление вектора на константу
     * @param con - константа
     * @return - результат деления
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
     * Векторное произведение двух векторов
     * @param vec
     * @return - результат векторного произведения
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
     * Модуль вектора
     * Длина вектора
     * @return - длина вектора
     */
    public double length()
    {
        return Math.sqrt((this.x * this.x) + 
        		(this.y * this.y) + 
        		(this.z * this.z));
    }
    
    /**
     * Нормализация вектора
     * @return - единичный вектор
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
     * Скалярное произведения двух векторов
     * @param vec
     */
    public double dot(Vector3D vec)
    {
        return this.x*vec.x + this.y*vec.y + this.z*vec.z;
    }
    
    /**
     * @return координата х
     */
    public double getX()
    {
        return this.x;
    }

    /**
     * @return координата y
     */
    public double getY()
    {
        return this.y;
    }
 
    /**
     * @return координата z
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
