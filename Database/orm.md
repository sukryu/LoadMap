# ORM과의 연계

1. ORM의 개념과 필요성
    1. ORM이란?
        * ORM(Object-Relational Mapping)은 객체 지향 프로그래밍의 객체(Object)와 관계형 데이터베이스(RDB)의 테이블을 자동으로 매핑해주는 기술입니다.
            ```java
            // ORM 사용 전 (Raw SQL)
            String sql = "INSERT INTO users (name, email) VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, "John");
            stmt.setString(2, "john@example.com");
            stmt.executeUpdate();

            // ORM 사용 후 (예: JPA)
            User user = new User();
            user.setName("John");
            user.setEmail("john@example.com");
            entityManager.persist(user);
            ```

    2. ORM의 필요성
        1. 생산성 향상
            - 반복적인 SQL 작성 감소
            - 데이터베이스 작업을 객체 지향적으로 처리
            - 자동 CRUD 쿼리 생성

        2. 유지보수성 향상
            - 테이블 스키마 변경 시 SQL 수정 최소화
            - 객체 중심의 코드 작성으로 가독성 향상
            - 비즈니스 로직에 집중 가능

        3. 데이터베이스 독립성
            - DB 벤더 교체 시 코드 수정 최소화
            - 다양한 데이터베이스 동시 지원
            - 방언(Dialect) 설정으로 DB 전환 용이

    3. ORM의 Trade-offs
        1. 장점
            - 직관적인 객체 중심 개발
            - 생산성과 유지보수성 향상
            - DB 추상화로 이식성 증가
            - 기본적인 CRUD 작업 자동화

        2. 단점
            ```sql
            -- ORM이 생성한 비효율적인 쿼리 예시
            SELECT * FROM orders o 
            JOIN order_items oi ON o.id = oi.order_id
            JOIN products p ON oi.product_id = p.id
            WHERE o.status = 'PENDING'
            -- 실제로는 일부 컬럼만 필요한데 모든 컬럼을 조회
            ```
            - 복잡한 쿼리의 경우 성능 최적화 어려움
            - 초기 학습 곡선이 높음
            - 직접 SQL 작성보다 세밀한 제어가 어려울 수 있음.
            - 잘못 사용 시 성능 저하(N+1 문제 등)

    4. SQL 지식과의 연계
        ```java
        // ORM의 JPQL
        String jpql = "SELECT o FROM Order o WHERE o.status = :status";
        TypedQuery<Order> query = em.createQuery(jpql, Order.class);
        query.setParameter("status", "PENDING");

        // Native SQL
        String sql = "SELECT * FROM orders WHERE status = ?";
        Query query = em.createNativeQuery(sql, Order.class);
        query.setParameter(1, "PENDING");
        ```
        - ORM을 효과적으로 사용하기 위해서는 SQL에 대한 이해가 필수
        - 쿼리 최적화와 성능 튜닝 시 SQL 지식 필요
        - Complex 쿼리는 Native SQL과 혼용하여 사용

## 대표적인 ORM 프레임워크 예시

1. Java/Hibernate(JPA)
    1. 기본 엔티티 매핑
        ```java
        @Entity
        @Table(name = "employees")
        public class Employee {
            @Id
            @GeneratedValue(strategy = GenerationType.IDENTITY)
            private Long id;

            @Column(name = "first_name", length = 50, nullable = false)
            private String firstName;

            @Column(name = "salary")
            private BigDecimal salary;

            @Temporal(TemporalType.TIMESTAMP)
            private Date hireDate;
        }
        ```

    2. 관계 매핑
        ```java
        @Entity
        public class Department {
            @Id
            @GeneratedValue(strategy = GenerationType.IDENTITY)
            private Long id;

            // 1:N 관계 매핑
            @OneToMany(mappedBy = "department", fetch = FetchType.LAZY)
            private List<Employee> employees = new ArrayList<>();

            // N:1 관계 매핑
            @ManyToOne
            @JoinColumn(name = "company_id")
            private Company company;
        }
        ```

    3. JPQL vs Native SQL
        ```java
        // JPQL 사용
        String jpql = "SELECT e FROM Employee e WHERE e.salary > :minSalary";
        List<Employee> employees = entityManager
            .createQuery(jpql, Employee.class)
            .setParameter("minSalary", new BigDecimal("50000"))
            .getResultList();

        // Native SQL 사용
        String sql = "SELECT * FROM employees WHERE salary > ?";
        List<Employee> employees = entityManager
            .createNativeQuery(sql, Employee.class)
            .setParameter(1, 50000)
            .getResultList();
        ```

    4. Lazy/Eager Loading
        ```java
        @Entity
        public class Employee {
            // 즉시 로딩 (Eager Loading)
            @ManyToOne(fetch = FetchType.EAGER)
            private Department department;

            // 지연 로딩 (Lazy Loading)
            @OneToMany(mappedBy = "employee", fetch = FetchType.LAZY)
            private List<Project> projects;
        }

        // N+1 문제 발생 예시
        List<Employee> employees = em.createQuery("SELECT e FROM Employee e", Employee.class)
            .getResultList();

        // 각 employee에 대해 추가 쿼리 발생
        for (Employee emp : employees) {
            System.out.println(emp.getDepartment().getName()); // 추가 쿼리 발생!
        }

        // N+1 문제 해결을 위한 JOIN FETCH 사용
        List<Employee> employees = em.createQuery(
            "SELECT e FROM Employee e JOIN FETCH e.department", 
            Employee.class
        ).getResultList();
        ```

    5. 트랜잭션 관리
        ```java
        @Transactional
        public void updateEmployeeSalary(Long empId, BigDecimal newSalary) {
            Employee emp = entityManager.find(Employee.class, empId);
            emp.setSalary(newSalary);
            // 트랜잭션 종료 시 자동으로 변경사항 반영
        }
        ```

    6. 캐싱 전략
        ```java
        @Entity
        @Cache(usage = CacheConcurrencyStrategy.READ_WRITE)
        public class Department {
            @Id
            private Long id;

            @OneToMany(mappedBy = "department")
            @Cache(usage = CacheConcurrencyStrategy.READ_ONLY)
            private Set<Employee> employees;
        }
        ```

    * 이러한 JPA/Hibernate의 기능들은 객체 지향적인 방식으로 데이터베이스를 다룰 수 있게 해주지만, 적절한 사용을 위해서는 내부적으로 생성되는 SQL과 실행 계획을 이해하는 것이 중요합니다.

2. Python/SQLAlchemy
    1. 기본 모델 정의 (Declarative Base)
        ```python
        from sqlalchemy import Column, Integer, String, ForeignKey, create_engine
        from sqlalchemy.ext.declarative import declarative_base
        from sqlalchemy.orm import relationship

        Base = declarative_base()

        class Employee(Base):
            __tablename__ = 'employees'
            
            id = Column(Integer, primary_key=True)
            name = Column(String(50), nullable=False)
            email = Column(String(100), unique=True)
            department_id = Column(Integer, ForeignKey('departments.id'))
            
            # 관계 설정
            department = relationship("Department", back_populates="employees")
        ```

    2. 세션 관리와 CRUD 작업
        ```python
        from sqlalchemy.orm import sessionmaker

        # 엔진 및 세션 설정
        engine = create_engine('postgresql://user:pass@localhost/dbname')
        Session = sessionmaker(bind=engine)
        session = Session()

        # Create
        new_emp = Employee(name="John Doe", email="john@example.com")
        session.add(new_emp)
        session.commit()

        # Read
        employees = session.query(Employee).filter(Employee.name.like('John%')).all()

        # Update
        employee = session.query(Employee).filter_by(id=1).first()
        employee.name = "John Smith"
        session.commit()

        # Delete
        session.delete(employee)
        session.commit()
        ```

    3. ORM vs Core API
        ```python
        # ORM 방식
        employees = session.query(Employee).filter(Employee.salary > 50000).all()

        # Core API 방식
        from sqlalchemy import select
        stmt = select(Employee.__table__).where(Employee.__table__.c.salary > 50000)
        result = session.execute(stmt)
        ```

    4. Alembic을 이용한 마이그레이션
        ```python
        # alembic/env.py
        from alembic import context
        from sqlalchemy import engine_from_config
        from models import Base

        target_metadata = Base.metadata

        # migrations/versions/xxxxx_create_employees.py
        from alembic import op
        import sqlalchemy as sa

        def upgrade():
            op.create_table(
                'employees',
                sa.Column('id', sa.Integer(), primary_key=True),
                sa.Column('name', sa.String(50), nullable=False),
                sa.Column('email', sa.String(100), unique=True)
            )

        def downgrade():
            op.drop_table('employees')
        ```
        ```bash
        # 마이그레이션 명령어
        alembic revision --autogenerate -m "Create employees table"
        alembic upgrade head
        ```

3. Python/Django ORM
    1. 모델 정의
        ```python
        from django.db import models

        class Department(models.Model):
            name = models.CharField(max_length=100)
            location = models.CharField(max_length=200)

        class Employee(models.Model):
            name = models.CharField(max_length=100)
            email = models.EmailField(unique=True)
            salary = models.DecimalField(max_digits=10, decimal_places=2)
            department = models.ForeignKey(
                Department,
                on_delete=models.CASCADE,
                related_name='employees'
            )
            created_at = models.DateTimeField(auto_now_add=True)
        ```

    2. QuerySet API 사용
        ```python
        # Create
        employee = Employee.objects.create(
            name="Jane Doe",
            email="jane@example.com",
            department_id=1
        )

        # Read with filtering and joining
        employees = Employee.objects.select_related('department').filter(
            salary__gt=50000
        ).order_by('-created_at')

        # Aggregate queries
        from django.db.models import Avg, Count
        dept_stats = Department.objects.annotate(
            employee_count=Count('employees'),
            avg_salary=Avg('employees__salary')
        )
        ```

    3. 마이그레이션
        ```bash
        # 마이그레이션 파일 생성
        python manage.py makemigrations

        # 마이그레이션 적용
        python manage.py migrate

        # 특정 앱의 마이그레이션 내역 확인
        python manage.py showmigrations myapp
        ```

    4. 최적화 기법
        ```python
        # N+1 문제 해결을 위한 select_related 사용
        employees = Employee.objects.select_related('department').all()

        # M:N 관계에서는 prefetch_related 사용
        departments = Department.objects.prefetch_related('employees').all()

        # 대량 생성 시 bulk_create 사용
        Employee.objects.bulk_create([
            Employee(name='User1', email='user1@example.com'),
            Employee(name='User2', email='user2@example.com'),
        ])
        ```

* 이처럼 Python에서는 SQLAlchemy와 Django ROM이 각각 다른 방식으로 ORM 기능을 제공합니다. SQLAlchemy는 좀 더 SQL에 가까운 우연한 인터페이스를 제공하는 반면, Django ORM은 좀 더 추상화된 고수준의 인터페이스를 제공합니다.

4. Go의 ORM과 데이터베이스 도구들
    1. GORM
        ```go
        // 모델 정의
        type Employee struct {
            gorm.Model               // ID, CreatedAt, UpdatedAt, DeletedAt 포함
            Name      string         `gorm:"size:255;not null"`
            Email     string         `gorm:"uniqueIndex"`
            Salary    decimal.Decimal
            DepartmentID uint
            Department  Department    `gorm:"foreignKey:DepartmentID"`
        }

        type Department struct {
            ID       uint
            Name     string
            Employees []Employee     `gorm:"foreignKey:DepartmentID"`
        }

        // DB 연결 및 마이그레이션
        db, err := gorm.Open(mysql.Open(dsn), &gorm.Config{})
        if err != nil {
            panic("failed to connect database")
        }
        db.AutoMigrate(&Employee{}, &Department{})

        // CRUD 작업
        // Create
        db.Create(&Employee{Name: "John", Email: "john@example.com"})

        // Read
        var employee Employee
        db.First(&employee, 1) // id로 찾기
        db.Where("name = ?", "John").First(&employee)

        // Update
        db.Model(&employee).Update("Name", "John Smith")

        // Delete
        db.Delete(&employee)

        // Hooks 사용
        func (e *Employee) BeforeCreate(tx *gorm.DB) (err error) {
            e.Email = strings.ToLower(e.Email)
            return
        }
        ```

    2. SQLC SQL 우선 접근 방식을 제공하는 코드 생성 도구
        ```sql
        -- queries.sql
        -- name: GetEmployee :one
        SELECT * FROM employees
        WHERE id = $1 LIMIT 1;

        -- name: ListEmployees :many
        SELECT * FROM employees
        WHERE department_id = $1;

        -- name: CreateEmployee :one
        INSERT INTO employees (name, email, department_id)
        VALUES ($1, $2, $3)
        RETURNING *;
        ```
        ```go
        // 생성된 Go 코드 사용
        employee, err := queries.GetEmployee(ctx, 1)
        if err != nil {
            log.Fatal(err)
        }

        employees, err := queries.ListEmployees(ctx, deptID)
        ```

    3. Ent (Facebook의 엔티티 프레임워크)스키마 기반 ORM으로 타입 안정성 제공
        ```go
        // 스키마 정의
        type Employee struct {
            ent.Schema
        }

        func (Employee) Fields() []ent.Field {
            return []ent.Field{
                field.String("name"),
                field.String("email").Unique(),
                field.Float("salary"),
            }
        }

        func (Employee) Edges() []ent.Edge {
            return []ent.Edge{
                edge.To("department", Department.Type),
            }
        }

        // 사용 예시
        client, err := ent.Open("sqlite3", "file:ent?mode=memory&cache=shared&_fk=1")
        if err != nil {
            log.Fatal(err)
        }

        // CRUD 작업
        employee, err := client.Employee.
            Create().
            SetName("John").
            SetEmail("john@example.com").
            Save(ctx)
        ```

    4. PGX PosgreSQL에 특화된 드라이버 및 툴킷
        ```go
        // 연결 풀 사용
        pool, err := pgxpool.Connect(context.Background(), os.Getenv("DATABASE_URL"))
        if err != nil {
            log.Fatal(err)
        }

        // 트랜잭션 처리
        tx, err := pool.Begin(context.Background())
        if err != nil {
            log.Fatal(err)
        }
        defer tx.Rollback(context.Background())

        // 배치 작업
        batch := &pgx.Batch{}
        batch.Queue("INSERT INTO employees (name) VALUES ($1)", "John")
        batch.Queue("INSERT INTO employees (name) VALUES ($1)", "Jane")

        br := pool.SendBatch(context.Background(), batch)
        defer br.Close()
        ```

    5. SQLBoiler
        - 데이터베이스 스키마로부터 타입 안전한 Go 코드 생성
        ```go
        // 자동 생성된 모델 사용
        employee, err := models.FindEmployee(ctx, db, employeeID)
        if err != nil {
            log.Fatal(err)
        }

        // 관계 로딩
        department, err := employee.Department().One(ctx, db)
        if err != nil {
            log.Fatal(err)
        }
        ```

* 각 도구의 특징:
    - GORM: 가장 널리 사용되는 Go ORM, Active Record 패턴 구현
    - SQLC: SQL 우선 접근으로 성능과 타입 안정성 강조
    - Ent: 스키마 중심 설계와 강력한 타입 시스템
    - PGX: PostgreSQL 특화 기능과 고성능
    - SQLBoiler: 데이터베이스 우선 접근과 코드 생성

* 선택 기준:
    1. 프로젝트 규모와 복잡성
    2. 성능 요구사항
    3. 팀의 SQL 친숙도
    4. 데이터베이스 특화 기능 필요 여부
    5. 개발 생산성 vs 유연성

* 각 도구는 자신만의 장단점이 있으므로, 프로젝트 요구사항에 따라 적절한 도구를 선택하는 것이 중요합니다.

5. 기타 언어별 대표적인 ORM
    1. Ruby on Rails - ActiveRecord
        ```ruby
        # 모델 정의
        class Employee < ApplicationRecord
        belongs_to :department
        has_many :projects
        validates :email, presence: true, uniqueness: true
        
        # 스코프 정의
        scope :active, -> { where(status: 'active') }
        scope :high_salary, -> { where('salary > ?', 50000) }
        end

        # CRUD 작업
        # Create
        employee = Employee.create(
        name: "John Doe",
        email: "john@example.com",
        department_id: 1
        )

        # Read with associations
        employees = Employee.includes(:department)
                        .where(status: 'active')
                        .order(created_at: :desc)

        # Update
        employee.update(salary: 60000)

        # Delete
        employee.destroy
        ```

    2. PHP Laravel - Eloquent
        ```php
        // 모델 정의
        class Employee extends Model
        {
            protected $fillable = ['name', 'email', 'salary'];

            public function department()
            {
                return $this->belongsTo(Department::class);
            }
        }

        // CRUD 및 쿼리 빌더
        // Create
        $employee = Employee::create([
            'name' => 'Jane Smith',
            'email' => 'jane@example.com'
        ]);

        // Read with conditions
        $employees = Employee::where('salary', '>', 50000)
                            ->with('department')
                            ->get();

        // Relationships
        $department->employees()->save($employee);
        ```

    3. Node.js - Sequelize
        ```javascript
        // 모델 정의
        const Employee = sequelize.define('Employee', {
        name: {
            type: DataTypes.STRING,
            allowNull: false
        },
        email: {
            type: DataTypes.STRING,
            unique: true
        }
        });

        // CRUD 작업
        // Create
        const employee = await Employee.create({
        name: 'Tom Wilson',
        email: 'tom@example.com'
        });

        // Read with associations
        const employees = await Employee.findAll({
        include: [{
            model: Department,
            where: { name: 'IT' }
        }],
        where: {
            salary: {
            [Op.gt]: 50000
            }
        }
        });
        ```

    4. C# - Entity Framework Core
        ```csharp
        // 모델 정의
        public class Employee
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public string Email { get; set; }
            public Department Department { get; set; }
        }

        // DbContext 설정
        public class AppDbContext : DbContext
        {
            public DbSet<Employee> Employees { get; set; }
            public DbSet<Department> Departments { get; set; }
        }

        // CRUD 및 LINQ 사용
        // Create
        var employee = new Employee { Name = "Alice Brown" };
        context.Employees.Add(employee);
        await context.SaveChangesAsync();

        // Query with LINQ
        var employees = await context.Employees
            .Where(e => e.Department.Name == "IT")
            .Include(e => e.Department)
            .ToListAsync();
        ```

    5. Rust - Diesel
        ```rust
        // 스키마 정의
        table! {
            employees (id) {
                id -> Int4,
                name -> Varchar,
                email -> Varchar,
            }
        }

        // 모델 정의
        #[derive(Queryable)]
        struct Employee {
            id: i32,
            name: String,
            email: String,
        }

        // CRUD 작업
        diesel::insert_into(employees::table)
            .values(&new_employee)
            .execute(&mut conn)?;

        let results = employees::table
            .filter(employees::department_id.eq(1))
            .load::<Employee>(&mut conn)?;
        ```
    
    * 각 ORM의 특징:
        1. ActiveRecord(Ruby)
            - Convention over Configurtion 원칙
            - 직관적이고 간결한 문법
            - 마이그레이션 시스템이 잘 갖쳐줘 있음

        2. Eloquent (PHP)
            - Laravel 프레임워크의 강력한 생태계
            - 우아한 문법과 쿼리 빌더
            - 이벤트/옵저버 패턴 지원

        3. Sequelize(Node.js)
            - 프로미스 기반 비동기 작업
            - 다양한 DB 지원 (MySQL, PostgreSQL, SQLite 등)
            - 트랜잭션과 관계 설정이 용이

        4. Entity Framework Core (C#)
            - LINQ를 통한 강력한 쿼리 기능
            - 마이그레이션 자동화
            - 비동기 작업 지원

        5. Diesel (Rust)
            - 컴파일 시점 타입 체크
            - 높은 성능
            - SQL과 가까운 추상화 레벨

    * 이러한 다양한 ORM들은 각 언어의 특성과 생태계에 맞춰 최적화되어 있으며, 해당 언어의 장점을 최대한 활용할 수 있도록 설계되어 있습니다.

## ORM의 내부 동작 원리

1. 매핑(Mapping)
    1. 클래스와 테이블 매핑
        ```java
        // Java JPA 예시
        @Entity
        @Table(name = "employees")
        public class Employee {
            @Id @GeneratedValue
            private Long id;
            
            @Column(name = "full_name", length = 100)
            private String name;
            
            @Temporal(TemporalType.TIMESTAMP)
            private Date hireDate;
            
            @Enumerated(EnumType.STRING)
            private EmployeeStatus status;
        }
        ```
        - 실제 생성되는 DDL:
            ```sql
            CREATE TABLE employees (
                id BIGINT PRIMARY KEY AUTO_INCREMENT,
                full_name VARCHAR(100),
                hire_date TIMESTAMP,
                status VARCHAR(20)
            );
            ```

    2. 자료형 변환 매핑
        ```python
        # SQLAlchemy 예시
        class Product(Base):
            __tablename__ = 'products'
            
            id = Column(Integer, primary_key=True)
            price = Column(Numeric(10, 2))  # Decimal로 매핑
            tags = Column(ARRAY(String))    # 배열 타입 매핑
            metadata = Column(JSON)         # JSON 타입 매핑
        ```
        - 데이터베이스 변환:
            ```python
            # Python 객체
            product = Product(
                price=Decimal('199.99'),
                tags=['electronics', 'new'],
                metadata={'color': 'black', 'weight': '150g'}
            )

            # 실제 DB 저장 시
            """
            INSERT INTO products (price, tags, metadata)
            VALUES (
                199.99,
                ARRAY['electronics', 'new'],
                '{"color": "black", "weight": "150g"}'
            )
            """
            ```

    3. 관계 매핑
        ```java
        // 1:1 관계
        @Entity
        public class Employee {
            @OneToOne
            @JoinColumn(name = "detail_id")
            private EmployeeDetail detail;
        }

        // 1:N 관계
        @Entity
        public class Department {
            @OneToMany(mappedBy = "department")
            private List<Employee> employees = new ArrayList<>();
        }

        // M:N 관계
        @Entity
        public class Project {
            @ManyToMany
            @JoinTable(
                name = "project_employees",
                joinColumns = @JoinColumn(name = "project_id"),
                inverseJoinColumns = @JoinColumn(name = "employee_id")
            )
            private Set<Employee> employees = new HashSet<>();
        }
        ```
        - 생성되는 테이블 구조:
            ```sql
            -- 1:1 관계
            CREATE TABLE employees (
                id BIGINT PRIMARY KEY,
                detail_id BIGINT UNIQUE,
                FOREIGN KEY (detail_id) REFERENCES employee_details(id)
            );

            -- 1:N 관계
            CREATE TABLE employees (
                id BIGINT PRIMARY KEY,
                department_id BIGINT,
                FOREIGN KEY (department_id) REFERENCES departments(id)
            );

            -- M:N 관계
            CREATE TABLE project_employees (
                project_id BIGINT,
                employee_id BIGINT,
                PRIMARY KEY (project_id, employee_id),
                FOREIGN KEY (project_id) REFERENCES projects(id),
                FOREIGN KEY (employee_id) REFERENCES employees(id)
            );
            ```

    4. 복합 키 매핑
        ```java
        @Entity
        public class OrderItem {
            @EmbeddedId
            private OrderItemId id;

            @MapsId("orderId")
            @ManyToOne
            private Order order;

            @MapsId("productId")
            @ManyToOne
            private Product product;
            
            private int quantity;
        }

        @Embeddable
        public class OrderItemId implements Serializable {
            private Long orderId;
            private Long productId;
        }
        ```

    * 이러한 매핑 메커니즘을 통해 ORM은 객체 모델과 관계형 데이터베이스 모델 간의 차이(임피던스 불일치)를 해결합니다. 개발자는 객체 지향적으로 코드를 작성하고, ORM이 이를 적절한 데이터베이스 구조로 변환하여 저장합니다.

2. 세션/엔티티 매니저
    1. 영속성 컨텍스트(Persistence Context)
        ```java
        // JPA 예시
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("myPU");
        EntityManager em = emf.createEntityManager();

        try {
            em.getTransaction().begin();
            
            // 영속성 컨텍스트에 엔티티 저장
            Employee emp = new Employee("John");
            em.persist(emp);  // 1차 캐시에 저장
            
            // 영속성 컨텍스트에서 조회
            Employee found = em.find(Employee.class, 1L);  // DB 조회 없이 캐시에서 반환
            
            em.getTransaction().commit();
        } finally {
            em.close();
        }
        ```

    2. 엔티티 상태 생명주기
        ```python
        # SQLAlchemy 예시
        from sqlalchemy.orm import Session

        # 1. Transient (비영속) 상태
        employee = Employee(name="Alice")  # 객체만 생성, 아직 세션과 무관

        # 2. Persistent (영속) 상태
        session.add(employee)  # 세션에 객체 추가
        session.commit()       # DB에 실제 반영

        # 3. Detached (준영속) 상태
        session.expunge(employee)  # 세션에서 분리

        # 4. Removed (삭제) 상태
        session.delete(employee)   # 삭제 마킹
        session.commit()          # DB에서 실제 삭제
        ```

    3. 세션 관리 예시
        ```java
        // Hibernate 세션 예시
        Session session = sessionFactory.openSession();
        Transaction tx = null;

        try {
            tx = session.beginTransaction();
            
            // 영속성 컨텍스트 작업
            Employee emp = session.get(Employee.class, 1L);  // 조회
            emp.setName("New Name");  // 변경 감지 대상이 됨
            
            // 중간 저장 및 초기화
            session.flush();  // 변경사항 DB 반영
            session.clear();  // 영속성 컨텍스트 초기화
            
            tx.commit();
        } catch (Exception e) {
            if (tx != null) tx.rollback();
            throw e;
        } finally {
            session.close();
        }
        ```

    4. 영속성 전이(Cascade)
        ```java
        @Entity
        public class Department {
            @Id @GeneratedValue
            private Long id;
            
            @OneToMany(mappedBy = "department", cascade = CascadeType.ALL)
            private List<Employee> employees = new ArrayList<>();
            
            public void addEmployee(Employee employee) {
                employees.add(employee);
                employee.setDepartment(this);
            }
        }

        // 사용 예시
        Department dept = new Department();
        dept.addEmployee(new Employee("John"));
        dept.addEmployee(new Employee("Alice"));

        // 부서 저장 시 직원도 함께 저장됨 (CASCADE)
        entityManager.persist(dept);
        ```

    5. 지연 로딩과 즉시 로딩
        ```java
        @Entity
        public class Employee {
            @ManyToOne(fetch = FetchType.LAZY)  // 지연 로딩
            private Department department;
            
            @OneToOne(fetch = FetchType.EAGER)  // 즉시 로딩
            private EmployeeDetail detail;
        }

        // 지연 로딩 동작
        Employee emp = em.find(Employee.class, 1L);
        // 이 시점에는 department가 프록시 객체

        dept = emp.getDepartment();  // 실제 사용 시점에 DB에서 로딩
        ```

    * 영속성 컨텍스트의 주요 이점:
        1. 1차 캐시
        2. 동일성 보장
        3. 변경 감지(Dirty Checking)
        4. 지연 로딩(Lazy Loading)
        5. 트랜잭션을 지원하는 쓰기 지연(Transactional Write-Behind)

    * 이러한 메커니즘을 통해 ORM은 객체 지향적인 방식으로 데이터베이스 작업을 수행하면서도, 성능과 데이터 일관성을 보장할 수 있습니다.

3. 쿼리 생성
    1. ORM의 통적 쿼리 생성
        ```java
        // JPA JPQL 예시
        // 엔티티 기반 쿼리
        String jpql = "SELECT e FROM Employee e WHERE e.salary > :minSalary";
        List<Employee> employees = em.createQuery(jpql, Employee.class)
            .setParameter("minSalary", 50000)
            .getResultList();

        // 실제 생성되는 SQL
        /*
        SELECT e.id, e.name, e.salary, e.department_id 
        FROM employees e 
        WHERE e.salary > 50000
        */
        ```

    2. 다양한 쿼리 방식
        ```java
        // 1. JPQL/HQL
        List<Employee> employees = em.createQuery(
            "SELECT e FROM Employee e JOIN e.department d WHERE d.name = :deptName", 
            Employee.class
        ).setParameter("deptName", "IT").getResultList();

        // 2. Native SQL
        List<Employee> employees = em.createNativeQuery(
            "SELECT * FROM employees WHERE department_id IN (SELECT id FROM departments WHERE location = ?)", 
            Employee.class
        ).setParameter(1, "Seoul").getResultList();

        // 3. Criteria API (동적 쿼리)
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Employee> cq = cb.createQuery(Employee.class);
        Root<Employee> employee = cq.from(Employee.class);

        // 동적 조건 구성
        List<Predicate> predicates = new ArrayList<>();

        if (name != null) {
            predicates.add(cb.like(employee.get("name"), "%" + name + "%"));
        }
        if (minSalary != null) {
            predicates.add(cb.greaterThan(employee.get("salary"), minSalary));
        }

        cq.where(predicates.toArray(new Predicate[0]));
        List<Employee> results = em.createQuery(cq).getResultList();
        ```

    3. QueryBuilder 패턴
        ```python
        # SQLAlchemy 예시
        from sqlalchemy import select

        # 기본 쿼리 빌더
        query = select(Employee).where(
            Employee.department_id == 1
        ).order_by(
            Employee.salary.desc()
        )

        # 조건부 쿼리 구성
        def build_search_query(name=None, min_salary=None, department=None):
            query = select(Employee)
            if name:
                query = query.where(Employee.name.like(f'%{name}%'))
            if min_salary:
                query = query.where(Employee.salary >= min_salary)
            if department:
                query = query.join(Department).where(Department.name == department)
            return query
        ```

    4. DML 쿼리 생성
        ```java
        // Insert 쿼리
        Employee emp = new Employee("John", 60000);
        em.persist(emp);
        // INSERT INTO employees (name, salary) VALUES ('John', 60000)

        // Update 쿼리
        Employee emp = em.find(Employee.class, 1L);
        emp.setSalary(65000);
        // UPDATE employees SET salary = 65000 WHERE id = 1

        // Delete 쿼리
        em.remove(emp);
        // DELETE FROM employees WHERE id = 1

        // Bulk 연산
        int updatedCount = em.createQuery(
            "UPDATE Employee e SET e.salary = e.salary * 1.1 WHERE e.department.id = :deptId"
        ).setParameter("deptId", 1L)
        .executeUpdate();
        ```

    5. 서브쿼리와 조인
        ```java
        // 서브쿼리 예시
        String jpql = """
            SELECT e FROM Employee e 
            WHERE e.salary > (
                SELECT AVG(e2.salary) 
                FROM Employee e2 
                WHERE e2.department = e.department
            )
        """;

        // 복잡한 조인 예시
        String jpql = """
            SELECT DISTINCT e FROM Employee e 
            LEFT JOIN FETCH e.department d 
            LEFT JOIN FETCH e.projects p 
            WHERE d.location IN ('Seoul', 'Busan')
        """;
        ```

    * 생성된 쿼리의 특징:
        1. 데이터베이스 방언(Dialect) 적용
        2. 성능 최적화(적절한 인덱스 사용)
        3. 타입 안정성 보장
        4. 동적 쿼리 생성 용이
        5. 페이징, 정렬 등 공통 기능 자동 지원

    * 이처럼 ORM은 다양한 방식으로 SQL을 생성하며, 개발자는 상황에 따라 적절한 쿼리 작성 방식을 선택할 수 있습니다.

4. 변경 감지(Dirty Checking)
    1. 기본 동작 원리
        ```java
        // JPA 예시
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();

        try {
            tx.begin();
            
            // 엔티티 조회
            Employee emp = em.find(Employee.class, 1L);
            
            // 엔티티 수정 - 별도의 update() 메서드 호출 없음
            emp.setName("New Name");  // 변경 감지 대상
            emp.setSalary(70000);     // 변경 감지 대상
            
            tx.commit();  // 커밋 시점에 변경 감지 동작
            // UPDATE employees SET name = ?, salary = ? WHERE id = ?
        } catch (Exception e) {
            tx.rollback();
            throw e;
        }
        ```

    2. 스냅샷 기반 비교
        ```python
        # SQLAlchemy 예시
        from sqlalchemy.orm import Session

        session = Session(engine)

        try:
            # 초기 상태 스냅샷 생성
            employee = session.query(Employee).get(1)
            # 내부적으로 {'name': 'John', 'salary': 60000} 스냅샷 저장
            
            # 엔티티 변경
            employee.name = "John Smith"
            employee.salary = 65000
            
            # 커밋 시 스냅샷과 비교하여 변경된 필드만 UPDATE
            session.commit()
        except:
            session.rollback()
            raise
        ```

    3. 변경 감지 최적화
        ```java
        @Entity
        @DynamicUpdate  // 변경된 필드만 UPDATE 쿼리에 포함
        public class Employee {
            @Id
            private Long id;
            
            private String name;
            
            @Column(updatable = false)  // 수정 불가 필드
            private LocalDateTime createdAt;
            
            @Version  // 동시성 제어를 위한 버전 관리
            private Long version;
        }
        ```

    4. Bulk 연산과 변경 감지
        ```java
        // 일반적인 변경 감지 (N번의 UPDATE)
        List<Employee> employees = em.createQuery("SELECT e FROM Employee e", Employee.class)
            .getResultList();

        for (Employee emp : employees) {
            emp.setSalary(emp.getSalary() * 1.1);  // 각각 변경 감지 발생
        }

        // Bulk 연산 (1번의 UPDATE)
        int updatedCount = em.createQuery(
            "UPDATE Employee e SET e.salary = e.salary * 1.1"
        ).executeUpdate();
        ```

    5. 변경 감지와 성능
        ```java
        @Entity
        public class Employee {
            @OneToMany(mappedBy = "employee", cascade = CascadeType.ALL)
            private List<Project> projects = new ArrayList<>();
            
            public void addProject(Project project) {
                projects.add(project);
                project.setEmployee(this);  // 양방향 관계 설정
            }
        }

        // 변경 감지 범위 제한
        @EntityListeners(AuditingEntityListener.class)
        public class BaseEntity {
            @LastModifiedDate
            private LocalDateTime updatedAt;
            
            @LastModifiedBy
            private String updatedBy;
        }
        ```

    * 변경 감지의 주요 특징:
        1. 자동 감지: 별도의 update() 메서드 호출 불필요
        2. 스냅샷 관리: 초기 상태와 비교하여 변경 감지
        3. 성능 최적화: 변경된 필드만 UPDATE 쿼리에 포함
        4. 트랜잭션 범위: 트랜잭션 커밋 시점에 동작
        5. 영속성 컨텍스트: 관리되는 엔티티만 대상

    * 변경 감지는 ORM의 핵심 기능 중 하나로, 객체 지향적인 코드 작성을 가능하게 하면서도 데이터베이스와의 동기화를 자동으로 처리해줍니다.

5. 캐싱
    1. 1차 캐시 (Session/영속성 컨텍스트 범위)
        ```java
        // JPA 예시
        EntityManager em = emf.createEntityManager();

        try {
            // 1차 캐시에 저장
            Employee emp1 = em.find(Employee.class, 1L);  // DB 조회
            Employee emp2 = em.find(Employee.class, 1L);  // 캐시에서 조회
            
            System.out.println(emp1 == emp2);  // true (동일성 보장)
            
            // 캐시 초기화
            em.clear();  // 1차 캐시 전체 초기화
            em.detach(emp1);  // 특정 엔티티만 캐시에서 제거
        } finally {
            em.close();  // 1차 캐시 소멸
        }
        ```

    2. 2차 캐시 (애플리케이션 전역)
        ```java
        @Entity
        @Cache(usage = CacheConcurrencyStrategy.READ_WRITE)
        public class Department {
            @Id
            private Long id;
            
            @Cache(usage = CacheConcurrencyStrategy.READ_ONLY)
            @OneToMany(mappedBy = "department")
            private List<Employee> employees = new ArrayList<>();
        }

        // 하이버네이트 2차 캐시 설정
        Properties props = new Properties();
        props.put("hibernate.cache.use_second_level_cache", "true");
        props.put("hibernate.cache.region.factory_class", 
                "org.hibernate.cache.ehcache.EhCacheRegionFactory");
        ```

    3. 쿼리 캐시
        ```java
        // 쿼리 결과 캐싱
        Query query = em.createQuery(
            "SELECT e FROM Employee e WHERE e.department.id = :deptId"
        );
        query.setHint("org.hibernate.cacheable", "true");
        query.setParameter("deptId", 1L);
        List<Employee> employees = query.getResultList();

        // NamedQuery with 캐시
        @Entity
        @NamedQuery(
            name = "Employee.findByDepartment",
            query = "SELECT e FROM Employee e WHERE e.department.id = :deptId",
            hints = @QueryHint(name = "org.hibernate.cacheable", value = "true")
        )
        public class Employee { ... }
        ```

    4. 캐시 전략
        ```java
        // 다양한 캐시 전략
        @Cache(usage = CacheConcurrencyStrategy.READ_ONLY)  // 읽기 전용
        @Cache(usage = CacheConcurrencyStrategy.NONSTRICT_READ_WRITE)  // 읽기-쓰기
        @Cache(usage = CacheConcurrencyStrategy.READ_WRITE)  // 엄격한 읽기-쓰기
        @Cache(usage = CacheConcurrencyStrategy.TRANSACTIONAL)  // 트랜잭션 지원

        // 캐시 영역 설정
        @Cache(region = "employee", usage = CacheConcurrencyStrategy.READ_WRITE)
        ```

    5. 캐시 레벨 비교
        ```plaintext
        1차 캐시:
        - 영속성 컨텍스트 범위
        - 객체 동일성(==) 보장
        - 트랜잭션 격리 수준 유지

        2차 캐시:
        - 애플리케이션 전체 범위
        - 동시성 고려 필요
        - L2 캐시 히트율 모니터링 중요

        DB 캐시:
        - 데이터베이스 서버 레벨
        - SQL 결과 캐싱
        - 모든 애플리케이션이 공유
        ```

    * 캐시 사용시 주의사항:
        1. 메모리 사용량 관리
        2. 캐시 정합성 유지
        3. 캐시 라이프사이클 관리
        4. 적절한 캐시 전략 선택
        5. 모니터링과 튜닝의 중요성

    * 각 캐시 레벨은 서로 다른 목적과 특성을 가지고 있으며, 적절한 사용을 통해 애플리케이션의 성능을 크게 향상시킬 수 있습니다.

## ORM과 SQL 최적화

1. N+1 문제
    1. N+1 문제 개요
        ```java
        // N+1 문제가 발생하는 코드
        // 1번의 부서 조회 + N번의 직원 조회
        List<Department> departments = em.createQuery(
            "SELECT d FROM Department d", Department.class
        ).getResultList();  // 1번 쿼리

        for (Department dept : departments) {
            // 각 부서마다 직원 조회 쿼리 실행 (N번)
            dept.getEmployees().size();  
        }
        ```

    2. 해결 방안
        1. Join Fetch를 사용한 즉시 로딩
            ```java
            // JPQL에서 JOIN FETCH 사용
            List<Department> departments = em.createQuery(
                "SELECT d FROM Department d JOIN FETCH d.employees",
                Department.class
            ).getResultList();  // 단 1번의 쿼리로 해결
            ```

        2. EntityGraph 사용
            ```java
            @EntityGraph(attributePaths = {"employees"})
            @Query("SELECT d FROM Department d")
            List<Department> findAllWithEmployees();
            ```

        3. Batch Size 설정
            ```java
            @Entity
            public class Department {
                @BatchSize(size = 100)  // 100개씩 일괄 조회
                @OneToMany(mappedBy = "department")
                private List<Employee> employees;
            }

            // 또는 글로벌 설정
            // hibernate.default_batch_fetch_size = 100
            ```

        4. Subquery Fetch
            ```java
            // 서브쿼리를 사용한 최적화
            List<Department> departments = em.createQuery(
                "SELECT d FROM Department d " +
                "WHERE d.id IN (SELECT e.department.id FROM Employee e)",
                Department.class
            ).getResultList();
            ```

    3. 성능 비교
        ```sql
        -- N+1 문제 발생 시 (N+1개의 쿼리)
        SELECT * FROM departments;  -- 1번
        SELECT * FROM employees WHERE department_id = ?;  -- N번 반복

        -- Join Fetch 사용 시 (1개의 쿼리)
        SELECT d.*, e.* 
        FROM departments d 
        LEFT JOIN employees e ON d.id = e.department_id;

        -- Batch Size 적용 시 (1 + ceil(N/batch_size)개의 쿼리)
        SELECT * FROM departments;
        SELECT * FROM employees 
        WHERE department_id IN (?, ?, ?, ...);  -- batch_size만큼
        ```

    4. 모니터링 및 디버깅
        ```java
        // SQL 로그 설정
        spring.jpa.properties.hibernate.show_sql=true
        spring.jpa.properties.hibernate.format_sql=true

        // 바인딩 파라미터 로깅
        logging.level.org.hibernate.type.descriptor.sql=trace

        // 성능 측정
        spring.jpa.properties.hibernate.generate_statistics=true
        ```

    * N+1 문제 방지를 위한 베스트 프랙티스:
        1. 연관 관계 설계 시 Fetch 전략 신중히 선택
        2. 필요한 데이터만 조회하도록 최적화
        3. Join Fetch와 Batch Size를 적절히 활용
        4. 엔티티 그래프 활용
        5. 쿼리 실행 계획 주기적 모니터링

    * 이러한 최적화 기법들을 통해 N+1 문제를 효과적으로 해결하고 애플리케이션의 성능을 향상시킬 수 있습니다.

2. 복잡 쿼리의 직접 작성
    1. 복잡한 집계 쿼리
        ```java
        // ORM 자동 생성 쿼리의 한계
        @Query("SELECT d.name, COUNT(e), AVG(e.salary) " +
            "FROM Department d LEFT JOIN d.employees e " +
            "GROUP BY d.name")
        List<Object[]> getDepartmentStats();

        // Native Query로 최적화
        @Query(value = """
            WITH monthly_stats AS (
                SELECT d.name, 
                    DATE_TRUNC('month', e.hire_date) as month,
                    COUNT(*) as emp_count,
                    AVG(salary) as avg_salary
                FROM departments d 
                LEFT JOIN employees e ON d.id = e.department_id
                GROUP BY d.name, DATE_TRUNC('month', e.hire_date)
            )
            SELECT * FROM monthly_stats
            WHERE avg_salary > (SELECT AVG(salary) FROM employees)
            """, nativeQuery = true)
        List<Object[]> getDetailedStats();
        ```

    2. 윈도우 함수 활용
        ```java
        -- Native Query로 작성해야 하는 복잡한 분석 쿼리
        @Query(value = """
            SELECT e.*, 
                salary,
                AVG(salary) OVER (PARTITION BY department_id) as dept_avg,
                salary - AVG(salary) OVER (PARTITION BY department_id) as diff_from_avg,
                RANK() OVER (PARTITION BY department_id ORDER BY salary DESC) as salary_rank
            FROM employees e
            """, nativeQuery = true)
        List<EmployeeStats> getEmployeeRankings();
        ```

    3. 동적 쿼리 최적화
        ```java
        // JPA Criteria API
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Employee> query = cb.createQuery(Employee.class);
        Root<Employee> employee = query.from(Employee.class);

        // 동적 조건 구성
        List<Predicate> predicates = new ArrayList<>();
        if (department != null) {
            predicates.add(cb.equal(employee.get("department"), department));
        }
        if (minSalary != null) {
            predicates.add(cb.greaterThan(employee.get("salary"), minSalary));
        }

        // 성능 최적화를 위한 인덱스 힌트 추가
        query.where(predicates.toArray(new Predicate[0]))
            .orderBy(cb.desc(employee.get("salary")));

        // Native SQL로 변환
        String sql = """
            SELECT /*+ INDEX(e emp_salary_idx) */ e.*
            FROM employees e
            WHERE (:department_id IS NULL OR department_id = :department_id)
            AND (:min_salary IS NULL OR salary >= :min_salary)
            ORDER BY salary DESC
            """;
        ```

    4. 대량의 데이터 처리
        ```java
        // JDBC batch 처리 활용
        @Modifying
        @Query(value = """
            INSERT INTO employee_archive (id, name, department, salary, archived_date)
            SELECT id, name, department, salary, CURRENT_TIMESTAMP
            FROM employees
            WHERE termination_date < :cutoffDate
            """, nativeQuery = true)
        void archiveOldEmployees(@Param("cutoffDate") LocalDate cutoffDate);

        // 벌크 연산 최적화
        @Modifying
        @Query("UPDATE Employee e SET e.salary = e.salary * 1.1 " +
            "WHERE e.department.id = :departmentId")
        int increaseSalaryForDepartment(@Param("departmentId") Long departmentId);
        ```

    5. 복잡한 조인과 서브쿼리
        ```java
        @Query(value = """
            WITH RECURSIVE emp_hierarchy AS (
                -- 기준 직원
                SELECT id, name, manager_id, 1 as level
                FROM employees
                WHERE manager_id IS NULL
                
                UNION ALL
                
                -- 재귀적으로 부하 직원 찾기
                SELECT e.id, e.name, e.manager_id, h.level + 1
                FROM employees e
                INNER JOIN emp_hierarchy h ON e.manager_id = h.id
            )
            SELECT * FROM emp_hierarchy
            ORDER BY level, name
            """, nativeQuery = true)
        List<Object[]> getEmployeeHierarchy();
        ```

    * 주의 사항과 팁:
        1. 복잡한 쿼리는 Native Query 사용을 두려워하지 말 것
        2. 실행 계획 확인과 성능 모니터링 필수
        3. 인덱스 활용 고려
        4. 대량 데이터 처리 시 배치 처리 활용
        5. ORM의 장점과 SQL의 장점을 적절히 조합
    
    * 이러한 방식으로 ORM의 편의성과 Native SQL의 강력함을 함께 활용할 수 있습니다.

3. 인덱스 설계
    1. ORM에서의 인덱스 정의
        ```java
        // JPA에서의 인덱스 정의
        @Entity
        @Table(name = "employees",
            indexes = {
                @Index(name = "idx_emp_email", columnList = "email", unique = true),
                @Index(name = "idx_emp_dept_salary", columnList = "department_id, salary")
            }
        )
        public class Employee {
            @Id
            private Long id;
            
            @Column(nullable = false)
            private String email;
            
            @ManyToOne
            @JoinColumn(name = "department_id")
            private Department department;
            
            private BigDecimal salary;
        }
        ```

    2. 복합 인덱스 설계
        ```java
        // 다중 컬럼 인덱스
        @Entity
        @Table(indexes = {
            @Index(name = "idx_search_optimization",
                columnList = "department_id, hire_date DESC, salary DESC")
        })
        public class Employee {
            // 자주 사용되는 검색 조건을 고려한 인덱스
            @Query("""
                SELECT e FROM Employee e
                WHERE e.department.id = :deptId
                AND e.hireDate >= :startDate
                ORDER BY e.salary DESC
                """)
            List<Employee> findByDepartmentWithSalary(
                @Param("deptId") Long departmentId,
                @Param("startDate") LocalDate startDate);
        }
        ```

    3. 수동 DDL 작성
        ```sql
        -- 직접 작성하는 인덱스 DDL
        CREATE INDEX CONCURRENTLY idx_employee_search 
        ON employees (department_id, hire_date DESC, salary DESC)
        WHERE status = 'ACTIVE';

        -- 부분 인덱스
        CREATE INDEX idx_high_salary_employees 
        ON employees (department_id, name)
        WHERE salary > 50000;
        ```

    4. 인덱스 모니터링과 관리
        ```java
        // 인덱스 사용 확인을 위한 로깅
        @Query(value = """
            EXPLAIN ANALYZE
            SELECT /*+ INDEX(e idx_emp_dept_salary) */ *
            FROM employees e
            WHERE department_id = ?
            AND salary >= ?
            """, nativeQuery = true)
        String explainQueryPlan(Long deptId, BigDecimal minSalary);
        ```

    5. 인덱스 설계 고려사항
        ```plaintext
        1. 선택도(Selectivity)
            - 높은 선택도: email, employee_id
            - 낮은 선택도: gender, status

        2. 데이터 분포
            - 균일 분포: 생성일자, 순차 ID
            - 비균일 분포: 부서별 직원 수

        3. 쿼리 패턴
            - 검색 조건 (WHERE 절)
            - 정렬 조건 (ORDER BY)
            - 조인 조건

        4. 데이터 변경 빈도
            - 읽기 중심 테이블: 더 많은 인덱스 허용
            - 쓰기 중심 테이블: 인덱스 최소화
        ```

    * 주의 사항과 베스트 프랙티스:
        1. 필요한 인덱스만 생성(과도한 인덱스는 성능 저하)
        2. 복합 인덱스 순서 최적화(선택도가 높은 컬럼을 앞에 배치)
        3. 인덱스 재구성 주기적 수행
        4. 실행 계획 모니터링
        5. 부분 인덱스 활용 검토

    * 이러한 인덱스 설계와 관리를 통해 ORM의 성능을 최적화할 수 있습니다.

4. 실행계획 분석
    1. ORM 쿼리 로깅과 실행계획
        ```java
        // JPA/Hibernate 로깅 설정
        spring.jpa.properties.hibernate.show_sql=true
        spring.jpa.properties.hibernate.format_sql=true
        spring.jpa.properties.hibernate.use_sql_comments=true

        // 실행계획 확인
        @Query(value = "EXPLAIN ANALYZE SELECT * FROM employees WHERE department_id = ?", 
            nativeQuery = true)
        String getQueryPlan(Long departmentId);
        ```

    2. 실행계획 분석과 최적화
        ```sql
        -- 실행계획 분석
        EXPLAIN ANALYZE
        SELECT e.*, d.name as dept_name
        FROM employees e
        INNER JOIN departments d ON e.department_id = d.id
        WHERE e.salary > 50000
        ORDER BY e.hire_date DESC;

        -- 실행계획 결과 예시
        /*
        Nested Loop  (cost=0.00..28.75 rows=150)
        ->  Index Scan using emp_salary_idx on employees e
            (cost=0.00..15.62 rows=100)
        ->  Index Scan using dept_pkey on departments d
            (cost=0.00..0.25 rows=1)
        */
        ```

    3. 옵티마이저 힌트 적용
        ```java
        // JPA에서 힌트 사용
        @QueryHints(value = {
            @QueryHint(name = "org.hibernate.comment", 
                    value = "/*+ INDEX(employees emp_idx) */")
        })
        List<Employee> findByDepartmentOptimized(Long departmentId);

        // Native Query에서 힌트 사용
        @Query(value = """
            SELECT /*+ INDEX(e emp_salary_dept_idx) */
                e.*, d.name as dept_name
            FROM employees e
            JOIN departments d ON e.department_id = d.id
            WHERE e.salary > :minSalary
            """, nativeQuery = true)
        List<Object[]> findHighSalaryEmployees(@Param("minSalary") BigDecimal minSalary);
        ```

    4. 성능 모니터링과 튜닝
        ```java
        // 성능 통계 활성화
        spring.jpa.properties.hibernate.generate_statistics=true
        spring.jpa.properties.hibernate.session.events.log.LOG_QUERIES_SLOWER_THAN_MS=25

        // 쿼리 실행 시간 측정
        @Autowired
        private EntityManager entityManager;

        public List<Employee> findEmployeesWithPerformanceLog() {
            long startTime = System.currentTimeMillis();
            
            List<Employee> result = entityManager
                .createQuery("SELECT e FROM Employee e", Employee.class)
                .getResultList();
            
            long endTime = System.currentTimeMillis();
            log.info("Query execution time: {} ms", endTime - startTime);
            
            return result;
        }
        ```

    5. 쿼리 튜닝 체크리스트
        ```plaintext
        1. 인덱스 활용 확인
            - 적절한 인덱스가 있는가?
            - 인덱스가 효율적으로 사용되고 있는가?

        2. 조인 최적화
            - 조인 순서가 적절한가?
            - 불필요한 조인이 없는가?

        3. 데이터 접근 패턴
            - N+1 문제가 발생하지 않는가?
            - 페이징이 효율적으로 동작하는가?

        4. 캐시 활용
            - 적절한 캐싱 전략을 사용하고 있는가?
            - 캐시 히트율은 적절한가?

        5. 배치 처리
            - 대량 데이터 처리 시 배치 처리를 활용하는가?
            - 적절한 배치 사이즈를 설정했는가?
        ```

    * 실행계획 분석 시 주의사항:
        1. 실제 데이터와 유사한 테스트 데이터 사용
        2. 장기적인 성능 모니터링
        3. 실행계획 변경 시 신중한 검토
        4. 캐시 영향 고려
        5. DB 벤더별 특성 이해

    * 이러한 실행계획 분석과 최적화를 통해 ORM의 성능을 지속적으로 개선할 수 있습니다.

## DB 마이그레이션 도구

1. 버전 관리
    1. Alembic (SQLAlchemy)
        ```python
        # migrations/env.py
        from alembic import context
        from sqlalchemy import engine_from_config
        from models import Base

        target_metadata = Base.metadata

        # migrations/versions/1a2b3c4d5e6f_create_employees.py
        def upgrade():
            op.create_table(
                'employees',
                sa.Column('id', sa.Integer(), primary_key=True),
                sa.Column('email', sa.String(255), unique=True),
                sa.Column('department_id', sa.Integer(), nullable=True),
                sa.ForeignKeyConstraint(['department_id'], ['departments.id'])
            )

        def downgrade():
            op.drop_table('employees')
        ```

    2. Flyway (Java)
        ```java
        -- V1__Create_employees.sql
        CREATE TABLE employees (
            id BIGINT PRIMARY KEY AUTO_INCREMENT,
            email VARCHAR(255) UNIQUE,
            department_id BIGINT,
            FOREIGN KEY (department_id) REFERENCES departments(id)
        );

        -- V2__Add_salary_column.sql
        ALTER TABLE employees
        ADD COLUMN salary DECIMAL(10,2);
        ```

    3. Django migrations
        ```python
        # migrations/0001_initial.py
        from django.db import migrations, models

        class Migration(migrations.Migration):
            initial = True

            dependencies = []

            operations = [
                migrations.CreateModel(
                    name='Employee',
                    fields=[
                        ('id', models.AutoField(primary_key=True)),
                        ('email', models.EmailField(unique=True)),
                        ('department', models.ForeignKey('Department', on_delete=models.CASCADE))
                    ],
                ),
            ]
        ```

2. Roll Forward/Backward
    1. 단계별 마이그레이션
        ```python
        # 1. 새 컬럼 추가
        def upgrade_v1():
            op.add_column('employees', 
                sa.Column('new_salary', sa.Numeric(10, 2))
            )

        # 2. 데이터 마이그레이션
        def upgrade_v2():
            op.execute("""
                UPDATE employees 
                SET new_salary = salary * 1.1
                WHERE department_id = 1
            """)

        # 3. 이전 컬럼 제거
        def upgrade_v3():
            op.drop_column('employees', 'salary')
            op.alter_column('employees', 'new_salary',
                        new_column_name='salary')
        ```

    2. CI/CD 파이프라인 연동
        ```yaml
        # GitHub Actions example
        name: Database Migration
        on:
        push:
            branches: [ main ]

        jobs:
        migrate:
            runs-on: ubuntu-latest
            steps:
            - uses: actions/checkout@v2
            
            - name: Run migrations
                run: |
                alembic upgrade head
                # or
                python manage.py migrate
                # or
                flyway migrate
        ```

    3. 무중단 배포 전략
        ```sql
        -- 1. 이전 버전과 호환되는 새 컬럼 추가
        ALTER TABLE employees ADD COLUMN new_email VARCHAR(255);

        -- 2. 애플리케이션에서 두 컬럼 동시 업데이트
        UPDATE employees SET new_email = email;

        -- 3. 새 버전 배포 후 이전 컬럼 제거
        ALTER TABLE employees DROP COLUMN email;
        ALTER TABLE employees RENAME COLUMN new_email TO email;
        ```

* 마이그레이션 도구의 장점:
    1. 버전 관리 자동화
    2. 롤백 가능성 확보
    3. 팁 협업 용이
    4. 배포 자동화 가능
    5. 스키마 변경 이력 추적

* 주의사항:
    1. 마이그레이션 순서 관리
    2. 대용량 데이터 마이그레이션 시 성능 고려
    3. 백업 및 롤백 계획 수립
    4. 데이터 정합성 검증
    5. 운영 환경 영향도 최소화

* 이러한 마이그레이션 도구를 활용하면 데이터베이스 스키마 변경을 보다 안전하고 효율적으로 관리할 수 있습니다.

## ORM과 Stored Procedure 연동 예제

1. 기본 모델 및 설정
    ```python
    # models.py
    from sqlalchemy import Column, Integer, String, Numeric, DateTime
    from sqlalchemy.ext.declarative import declarative_base

    Base = declarative_base()

    class Employee(Base):
        __tablename__ = 'employees'
        
        id = Column(Integer, primary_key=True)
        name = Column(String(50), nullable=False)
        department = Column(String(50))
        salary = Column(Numeric(10, 2))
        hire_date = Column(DateTime)

    # database.py
    from sqlalchemy import create_engine
    from sqlalchemy.orm import sessionmaker

    DATABASE_URL = "postgresql://user:pass@localhost/dbname"
    engine = create_engine(DATABASE_URL)
    SessionLocal = sessionmaker(bind=engine)
    ```

2. Stored Procedure 생성
    ```sql
    -- 부서별 급여 통계를 계산하는 프로시저
    CREATE OR REPLACE PROCEDURE calculate_department_stats(
        IN p_department VARCHAR(50),
        OUT p_avg_salary NUMERIC,
        OUT p_total_employees INTEGER
    )
    LANGUAGE plpgsql
    AS $$
    BEGIN
        SELECT AVG(salary), COUNT(*)
        INTO p_avg_salary, p_total_employees
        FROM employees
        WHERE department = p_department;
    END;
    $$;

    -- 급여 인상 프로시저
    CREATE OR REPLACE PROCEDURE increase_salary(
        IN p_department VARCHAR(50),
        IN p_increase_rate NUMERIC
    )
    LANGUAGE plpgsql
    AS $$
    BEGIN
        UPDATE employees
        SET salary = salary * (1 + p_increase_rate)
        WHERE department = p_department;
    END;
    $$;
    ```

3. ORM과 Stored Procedure 연동
    ```python
    # operations.py
    from sqlalchemy import text
    from datetime import datetime
    from decimal import Decimal
    from database import SessionLocal
    from models import Employee

    class EmployeeService:
        def __init__(self):
            self.db = SessionLocal()

        def create_employee(self, name: str, department: str, salary: Decimal):
            """ORM을 사용한 기본 CRUD"""
            try:
                employee = Employee(
                    name=name,
                    department=department,
                    salary=salary,
                    hire_date=datetime.now()
                )
                self.db.add(employee)
                self.db.commit()
                return employee
            except Exception as e:
                self.db.rollback()
                raise e

        def get_department_stats(self, department: str):
            """Stored Procedure 호출"""
            try:
                result = self.db.execute(
                    text("CALL calculate_department_stats(:dept, :avg, :count)"),
                    {
                        "dept": department,
                        "avg": 0.0,  # OUT 파라미터
                        "count": 0   # OUT 파라미터
                    }
                )
                return dict(result.mappings())
            except Exception as e:
                print(f"Error calling stored procedure: {e}")
                raise e

        def increase_department_salary(self, department: str, increase_rate: float):
            """복잡한 업데이트는 Stored Procedure 사용"""
            try:
                self.db.execute(
                    text("CALL increase_salary(:dept, :rate)"),
                    {
                        "dept": department,
                        "rate": increase_rate
                    }
                )
                self.db.commit()
            except Exception as e:
                self.db.rollback()
                raise e
    ```

4. 실제 사용 예시
    ```python
    # main.py
    from decimal import Decimal
    from operations import EmployeeService

    def main():
        service = EmployeeService()

        # ORM을 사용한 기본 CRUD
        new_employee = service.create_employee(
            name="John Doe",
            department="IT",
            salary=Decimal("50000.00")
        )
        print(f"Created employee: {new_employee.name}")

        # Stored Procedure를 통한 통계 확인
        stats = service.get_department_stats("IT")
        print(f"IT 부서 통계:")
        print(f"평균 급여: {stats['p_avg_salary']}")
        print(f"총 직원 수: {stats['p_total_employees']}")

        # Stored Procedure를 통한 급여 인상
        service.increase_department_salary("IT", 0.1)  # 10% 인상
        print("급여 인상 완료")

    if __name__ == "__main__":
        main()
    ```

5. 타 언어에서의 연동
    1. Java (JPA/Hibernate)
        ```java
        // Entity
        @Entity
        @Table(name = "employees")
        public class Employee {
            @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
            private Long id;
            private String name;
            private String department;
            private BigDecimal salary;
        }

        // Stored Procedure 호출
        @Repository
        public class EmployeeRepository {
            @PersistenceContext
            private EntityManager em;

            // 일반 ORM 사용
            public void save(Employee employee) {
                em.persist(employee);
            }

            // Stored Procedure 호출
            public List<Object[]> getDepartmentStats(String department) {
                StoredProcedureQuery query = em
                    .createStoredProcedureQuery("calculate_department_stats")
                    .registerStoredProcedureParameter("p_department", String.class, ParameterMode.IN)
                    .registerStoredProcedureParameter("p_avg_salary", BigDecimal.class, ParameterMode.OUT)
                    .registerStoredProcedureParameter("p_total_employees", Integer.class, ParameterMode.OUT)
                    .setParameter("p_department", department);

                query.execute();
                return Arrays.asList(
                    query.getOutputParameterValue("p_avg_salary"),
                    query.getOutputParameterValue("p_total_employees")
                );
            }
        }
        ```

    2. Node.js (Sequelize)
        ```javascript
        // Model
        const Employee = sequelize.define('Employee', {
        name: DataTypes.STRING,
        department: DataTypes.STRING,
        salary: DataTypes.DECIMAL(10, 2)
        });

        // Stored Procedure 호출
        async function getDepartmentStats(department) {
        const [results] = await sequelize.query(
            'CALL calculate_department_stats(:department, @avg, @count)',
            {
            replacements: { department },
            type: QueryTypes.RAW
            }
        );

        const [[stats]] = await sequelize.query(
            'SELECT @avg as avg_salary, @count as total_employees'
        );
        
        return stats;
        }

        // 사용 예시
        async function main() {
        // ORM 사용
        const employee = await Employee.create({
            name: 'John',
            department: 'IT',
            salary: 50000
        });

        // Stored Procedure 호출
        const stats = await getDepartmentStats('IT');
        console.log(stats);
        }
        ```

    3. C# (Entity Framework)
        ```csharp
        // Entity
        public class Employee
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public string Department { get; set; }
            public decimal Salary { get; set; }
        }

        // Context
        public class AppDbContext : DbContext
        {
            public DbSet<Employee> Employees { get; set; }

            // Stored Procedure 매핑
            public virtual async Task<DepartmentStats> GetDepartmentStatsAsync(
                string department)
            {
                var paramDepartment = new SqlParameter("@Department", department);
                var paramAvgSalary = new SqlParameter
                {
                    ParameterName = "@AvgSalary",
                    SqlDbType = SqlDbType.Decimal,
                    Direction = ParameterDirection.Output
                };
                var paramCount = new SqlParameter
                {
                    ParameterName = "@TotalEmployees",
                    SqlDbType = SqlDbType.Int,
                    Direction = ParameterDirection.Output
                };

                await Database.ExecuteSqlRawAsync(
                    "EXEC calculate_department_stats @Department, @AvgSalary OUT, @TotalEmployees OUT",
                    paramDepartment, paramAvgSalary, paramCount);

                return new DepartmentStats
                {
                    AvgSalary = (decimal)paramAvgSalary.Value,
                    TotalEmployees = (int)paramCount.Value
                };
            }
        }

        // 사용 예시
        public async Task ProcessEmployeeData()
        {
            using var context = new AppDbContext();
            
            // ORM 사용
            var employee = new Employee
            {
                Name = "Alice",
                Department = "IT",
                Salary = 60000M
            };
            context.Employees.Add(employee);
            await context.SaveChangesAsync();

            // Stored Procedure 호출
            var stats = await context.GetDepartmentStatsAsync("IT");
            Console.WriteLine($"Average Salary: {stats.AvgSalary}");
        }
        ```

    4. Ruby on Rails (Active Record)
        ```ruby
        # Model
        class Employee < ApplicationRecord
        # Stored Procedure 호출 메서드
        def self.department_stats(department)
            result = ActiveRecord::Base.connection.execute(
            "CALL calculate_department_stats(?, @avg, @count)", 
            [department]
            )
            
            stats = ActiveRecord::Base.connection.execute(
            "SELECT @avg as avg_salary, @count as total_employees"
            ).first
            
            OpenStruct.new(
            avg_salary: stats['avg_salary'],
            total_employees: stats['total_employees']
            )
        end
        end

        # 사용 예시
        # ORM 사용
        employee = Employee.create!(
        name: 'Bob',
        department: 'IT',
        salary: 55000
        )

        # Stored Procedure 호출
        stats = Employee.department_stats('IT')
        puts "Average Salary: #{stats.avg_salary}"
        ```

* 이 처럼 각 언어와 프레임워크는 자신만의 방식으로 ORM과 Stored Procedure를 연동할 수 있는 기능을 제공합니다. 어떤 방식을 선택하든 중요한 점은:
    1. ORM의 편의성과 Stored Procedure의 성능을 적절히 조합
    2. 트랜잭션 관리에 주의
    3. 에러 처리 구현
    4. 데이터베이스 연결 관리
    5. 테스트 용이성 확보

    - 이러한 점들을 고려하여 구현하면 됩니다.

## 모범 사례 & 주의사항

1. CRUD와 복잡한 DB 로직의 분리
    ```java
    // 좋은 예: 단순 CRUD는 ORM 사용
    @Service
    public class EmployeeService {
        // 간단한 CRUD - ORM 사용
        public Employee createEmployee(Employee employee) {
            return employeeRepository.save(employee);
        }

        // 복잡한 로직 - Stored Procedure 사용
        public void processBatchSalaryUpdate() {
            entityManager.createNativeQuery("CALL update_department_salaries")
                        .executeUpdate();
        }

        // 복잡한 집계 - Native Query 사용
        public List<DepartmentStats> getDepartmentStats() {
            return entityManager.createNativeQuery("""
                SELECT d.name, 
                    COUNT(e.id) as emp_count,
                    AVG(e.salary) as avg_salary,
                    SUM(e.salary) as total_salary
                FROM departments d
                LEFT JOIN employees e ON d.id = e.department_id
                GROUP BY d.name
                HAVING COUNT(e.id) > 0
                """, "DepartmentStatsMapping")
                .getResultList();
        }
    }
    ```

2. 엔티티 설계 최적화
    ```java
    // 나쁜 예: 무분별한 양방향 매핑
    @Entity
    public class Department {
        @OneToMany(mappedBy = "department", fetch = FetchType.LAZY)
        private List<Employee> employees;
    }

    @Entity
    public class Employee {
        @ManyToOne(fetch = FetchType.LAZY)
        private Department department;
        
        @ManyToMany
        private List<Project> projects;
    }

    // 좋은 예: 필요한 관계만 정의하고 적절한 Fetch 전략 사용
    @Entity
    public class Department {
        @OneToMany(mappedBy = "department")
        @BatchSize(size = 100)  // N+1 문제 방지
        private Set<Employee> employees;  // List 대신 Set 사용
    }

    @Entity
    public class Employee {
        @ManyToOne(fetch = FetchType.LAZY)
        @JoinColumn(name = "department_id")
        private Department department;
    }
    ```

3. 트랜잭션 관리
    ```java
    // 트랜잭션 전파 설정
    @Transactional(propagation = Propagation.REQUIRED)
    public class EmployeeService {
        
        @Transactional(readOnly = true)  // 읽기 전용 트랜잭션
        public Employee findById(Long id) {
            return repository.findById(id);
        }

        @Transactional(rollbackFor = CustomException.class)  // 특정 예외에서만 롤백
        public void updateEmployee(Employee emp) {
            // 업데이트 로직
        }

        // 중첩 트랜잭션 처리
        @Transactional(propagation = Propagation.REQUIRES_NEW)
        public void processCriticalOperation() {
            // 별도 트랜잭션으로 처리
        }
    }
    ```

4. DB 스키마 변경 관리
    ```python
    # Alembic 마이그레이션 예시
    """revision_001.py"""
    def upgrade():
        # 안전한 스키마 변경
        op.add_column('employees', sa.Column('email', sa.String(255)))
        op.execute("""
            UPDATE employees 
            SET email = CONCAT(LOWER(name), '@company.com')
        """)
        op.alter_column('employees', 'email', nullable=False)

    def downgrade():
        op.drop_column('employees', 'email')
    ```

5. 성능 모니터링
    ```java
    // 성능 모니터링 설정
    @Configuration
    public class JpaConfig {
        @Bean
        public DataSource dataSource() {
            HikariConfig config = new HikariConfig();
            config.setMaximumPoolSize(10);
            config.setMinimumIdle(5);
            config.setConnectionTimeout(30000);
            return new HikariDataSource(config);
        }
    }

    // 쿼리 로깅 및 성능 측정
    @Aspect
    @Component
    public class QueryPerformanceMonitor {
        @Around("execution(* org.hibernate.Session.*(..))")
        public Object measureQueryPerformance(ProceedingJoinPoint pjp) throws Throwable {
            long start = System.currentTimeMillis();
            Object result = pjp.proceed();
            long executionTime = System.currentTimeMillis() - start;
            
            if (executionTime > 1000) {  // 1초 이상 걸리는 쿼리 로깅
                log.warn("Slow query detected: {} ms", executionTime);
            }
            
            return result;
        }
    }
    ```

* 주요 체크리스트:
    1. 단순/복잡 로직 분리
        - 단순 CRUD -> ORM
        - 복잡한 로직 -> Stored Procedure/Native Query

    2. 엔티티 설계 최적화
        - 양방향 매핑 최소화
        - 적절한 Fetch 전략 선택
        - Batch Size 설정으로 N+1 문제 해결

    3. 트랜잭션 관리
        - 적절한 트랜잭션 경계 설정
        - 전파 속성 이해
        - 롤백 전략 수립

    4. 스키마 변경 관리
        - 마이그레이션 도구 활용
        - 변경 이력 관리
        - 롤백 계획 수립

    5. 성능 모니터링
        - 쿼리 로깅
        - 실행 계획 분석
        - 캐시 히트율 모니터링
        - Connection Pool 관리

* 이러한 모범 사례와 주의사항을 준수하면 ORM을 효과적으로 활용할 수 있습니다.