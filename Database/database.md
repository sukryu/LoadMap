<h2>데이터베이스 연동</h2>
<p>NestJS 애플리케이션에서 데이터베이스를 연동하고 활용하는 것은 매우 중요합니다. 데이터베이스 연동을 통해 데이터의 영속성을 보장하고, 비즈니스 로직을 구현할 수 있습니다. 다양한 데이터베이스와 ORM/ODM 라이브러리를 선택하여 사용할 수 있으며, 데이터베이스 설계와 최적화 등의 심화 개념을 이해하고 적용해야 합니다.</p>
<h3>데이터베이스 선택</h3>
<ul>
  <li>관계형 데이터베이스 (RDBMS)
    <ul>
      <li>MySQL: 오픈소스 RDBMS로 널리 사용되며, 중소규모 애플리케이션에 적합합니다.</li>
      <li>PostgreSQL: 오픈소스 RDBMS로 확장성과 성능이 우수하며, 대규모 애플리케이션에 적합합니다.</li>
      <li>기타: Oracle, SQL Server, MariaDB 등 다양한 상용 및 오픈소스 RDBMS가 있습니다.</li>
    </ul>
  </li>
  <li>NoSQL 데이터베이스
    <ul>
      <li>MongoDB: 도큐먼트 기반의 NoSQL 데이터베이스로, 유연한 스키마와 확장성을 제공합니다.</li>
      <li>Redis: 인메모리 Key-Value 스토어로, 캐싱과 빠른 데이터 액세스에 사용됩니다.</li>
      <li>Cassandra: 와이드 칼럼 스토어로, 대규모 분산 시스템에 적합합니다.</li>
    </ul>
  </li>
</ul>
<p>프로젝트의 요구사항과 데이터 구조에 맞는 데이터베이스를 선택해야 합니다. 관계형 데이터베이스는 정규화된 데이터와 복잡한 쿼리에 적합하고, NoSQL 데이터베이스는 유연성과 확장성이 필요한 경우에 사용됩니다.</p>
<h3>ORM/ODM 활용</h3>
<ul>
  <li>ORM (Object-Relational Mapping)
    <ul>
      <li>Sequelize: Node.js에서 사용되는 Promise 기반의 ORM으로, 다양한 RDBMS를 지원합니다.</li>
      <li>TypeORM: TypeScript 기반의 ORM으로, Active Record와 Data Mapper 패턴을 모두 지원합니다.</li>
      <li>기타: Objection.js, Knex.js 등의 Query Builder 라이브러리도 사용할 수 있습니다.</li>
    </ul>
  </li>
  <li>ODM (Object-Document Mapping)
    <ul>
      <li>Mongoose: MongoDB를 위한 ODM 라이브러리로, 스키마 정의와 쿼리 작성을 간편하게 해줍니다.</li>
    </ul>
  </li>
</ul>
<p>ORM과 ODM을 사용하면 데이터베이스 작업을 객체 지향적으로 처리할 수 있어 생산성을 높일 수 있습니다. 데이터베이스 쿼리를 직접 작성하는 대신 객체 모델을 통해 데이터를 조작할 수 있습니다.</p>
<p>NestJS에서는 @nestjs/sequelize, @nestjs/typeorm, @nestjs/mongoose 등의 패키지를 통해 ORM/ODM을 손쉽게 통합할 수 있습니다.</p>
<pre><code class="language-typescript">// Sequelize 모델 정의 예시
import { Column, Model, Table } from 'sequelize-typescript';
@Table
export class User extends Model {
@Column
name: string;
@Column
email: string;
}
// TypeORM 엔티티 정의 예시
import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';
@Entity()
export class User {
@PrimaryGeneratedColumn()
id: number;
@Column()
name: string;
@Column()
email: string;
}
// Mongoose 스키마 정의 예시
import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose';
import { Document } from 'mongoose';
@Schema()
export class User extends Document {
@Prop()
name: string;
@Prop()
email: string;
}
export const UserSchema = SchemaFactory.createForClass(User);
</code></pre>
<h3>데이터베이스 스키마 설계</h3>
<p>데이터베이스 스키마는 데이터의 구조와 관계를 정의하는 청사진입니다. 효과적인 스키마 설계를 통해 데이터 무결성을 보장하고, 성능을 최적화할 수 있습니다.</p>
<ul>
  <li>정규화 (Normalization): 데이터의 중복을 제거하고, 테이블을 분리하여 데이터의 일관성을 유지하는 과정입니다. 정규화를 통해 데이터의 변경에 따른 이상 현상을 방지할 수 있습니다.</li>
  <li>관계 설정: 테이블 간의 관계를 정의하여 데이터의 연결성을 확보합니다. 1:1, 1:N, M:N 등의 관계를 적절히 설정해야 합니다.</li>
  <li>인덱스 설계: 인덱스를 사용하여 데이터 검색 속도를 향상시킬 수 있습니다. 적절한 인덱스를 생성하여 쿼리 성능을 최적화해야 합니다.</li>
</ul>
<h3>쿼리 최적화</h3>
<p>데이터베이스 쿼리의 성능을 최적화하여 애플리케이션의 응답 속도를 향상시킬 수 있습니다.</p>
<ul>
  <li>효율적인 쿼리 작성: 불필요한 데이터를 가져오지 않도록 SELECT 절에 필요한 컬럼만 지정하고, 적절한 조건절을 사용하여 데이터의 범위를 제한합니다.</li>
  <li>조인 최소화: 가능한 한 조인을 최소화하고, 서브쿼리를 활용하여 쿼리를 최적화합니다.</li>
  <li>인덱스 활용: WHERE 절에 사용되는 컬럼에 인덱스를 생성하여 검색 속도를 향상시킵니다. 복합 인덱스를 사용하여 다중 컬럼 검색을 최적화할 수 있습니다.</li>
  <li>쿼리 분석: 데이터베이스의 쿼리 실행 계획을 분석하여 쿼리의 병목 지점을 파악하고 개선합니다. EXPLAIN 키워드를 사용하여 쿼리의 실행 계획을 확인할 수 있습니다.</li>
</ul>
<h3>데이터베이스 고급 기능</h3>
<p>데이터베이스의 고급 기능을 활용하여 데이터의 일관성과 안정성을 보장할 수 있습니다.</p>
<ul>
  <li>트랜잭션 (Transaction): 데이터베이스의 상태를 변경하는 작업 단위로, ACID 특성을 보장합니다. 트랜잭션을 사용하여 데이터의 일관성을 유지할 수 있습니다.</li>
  <li>락 (Lock): 데이터에 대한 동시 접근을 제어하여 데이터의 무결성을 보장합니다. 공유 락(Shared Lock)과 배타 락(Exclusive Lock)을 사용하여 읽기와 쓰기 작업을 관리합니다.</li>
  <li>복제 (Replication): 데이터베이스를 여러 노드로 복제하여 데이터의 가용성과 내결함성을 높입니다. 마스터-슬레이브 복제, 마스터-마스터 복제 등의 방식을 사용할 수 있습니다.</li>
  <li>샤딩 (Sharding): 대량의 데이터를 여러 개의 데이터베이스 서버로 분산 저장하여 확장성을 확보합니다. 데이터를 파티셔닝하여 각 샤드에 분산 저장함으로써 읽기/쓰기 성능을 향상시킬 수 있습니다.</li>
</ul>
<pre><code class="language-typescript">// Sequelize를 사용한 트랜잭션 예시
import { Sequelize } from 'sequelize-typescript';
const sequelize = new Sequelize({...});
await sequelize.transaction(async (t) => {
const user = await User.create({ name, email }, { transaction: t });
await Profile.create({ userId: user.id, bio }, { transaction: t });
});
// TypeORM을 사용한 락 예시
import { getConnection } from 'typeorm';
const connection = getConnection();
const queryRunner = connection.createQueryRunner();
await queryRunner.connect();
await queryRunner.startTransaction();
try {
const user = await queryRunner.manager.findOne(User, 1, { lock: { mode: 'pessimistic_write' } });
// 데이터 수정 작업 수행
await queryRunner.manager.save(user);
await queryRunner.commitTransaction();
} catch (err) {
await queryRunner.rollbackTransaction();
} finally {
await queryRunner.release();
}
</code></pre>
<p>위의 예시 코드는 Sequelize를 사용한 트랜잭션 처리와 TypeORM을 사용한 락 처리를 보여줍니다. 트랜잭션을 사용하여 데이터의 일관성을 보장하고, 락을 사용하여 데이터에 대한 동시 접근을 제어할 수 있습니다.</p>
<p>데이터베이스 연동은 NestJS 애플리케이션의 핵심 기능 중 하나입니다. 적절한 데이터베이스와 ORM/ODM을 선택하고, 효과적인 스키마 설계와 쿼리 최적화를 통해 데이터 액세스 성능을 향상시킬 수 있습니다. 또한 트랜잭션, 락, 복제, 샤딩 등의 고급 기능을 활용하여 데이터의 일관성과 가용성을 보장할 수 있습니다. NestJS의 모듈 시스템과 DI를 활용하여 데이터베이스 연동을 모듈화하고 추상화하면 유지보수성과 확장성을 높일 수 있습니다.</p>