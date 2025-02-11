export type ResourceStatus = 'provisioning' | 'running' | 'stopped';

export abstract class CloudResource {
    private _id: string;
    private _name: string;
    protected _status: ResourceStatus;

    constructor(id: string, name: string) {
        this._id = id;
        this._name = name;
        this._status = 'stopped';
    }

    get id(): string {
        return this._id;
    }

    get name(): string {
        return this._name;
    }

    get status(): ResourceStatus {
        return this._status;
    }

    /**
     * 리소스를 프로비저닝하는 비동기 메서드
     * @throws {Error} 프로비저닝 실패 시 발생할 수 있는 에러
     * @returns Promise<void> 프로비저닝 완료 시 resolve
     */
    abstract provision(): Promise<void>;

    /**
     * 리소스를 종료(terminate)하는 비동기 메서드
     * @throws {Error} 종료 실패 시 발생할 수 있는 에러
     * @returns Promise<void> 종료 완료 시 resolve
     */
    abstract terminate(): Promise<void>;
}