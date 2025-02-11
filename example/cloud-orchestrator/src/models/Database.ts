import { CloudResource } from "./CloudResource";

export type DatabaseEngine = "MySQL" | "PostgreSQL";

export class Database extends CloudResource {
    private _engine: DatabaseEngine;
    private _storage: number;

    constructor(id: string, name: string, engine: DatabaseEngine, storage: number) {
        super(id, name);
        this._engine = engine;
        this._storage = storage;
    }

    get engine(): DatabaseEngine {
        return this._engine;
    }

    get storage(): number {
        return this._storage;
    }

    async provision(): Promise<void> {
        this._status = 'provisioning';
        
        try {
            const provisioningTime = Math.floor(Math.random() * 2000) + 1000;
            await new Promise(resolve => setTimeout(resolve, provisioningTime));
            
            if (Math.random() < 0.2) {
                throw new Error(`Failed to provision Database ${this.id}: Configuration failed`);
            }
            
            this._status = 'running';
            console.log(`Database ${this.id} (${this.name}) successfully provisioned with ${this._engine} Engine and ${this._storage}GB storage`);
        } catch (error) {
            this._status = 'stopped';
            throw error;
        }
    }
    
    async terminate(): Promise<void> {
        try {
            const terminationTime = Math.floor(Math.random() * 1000) + 500;
            await new Promise(resolve => setTimeout(resolve, terminationTime));
            
            this._status = 'stopped';
            console.log(`Database ${this.id} (${this.name}) successfully terminated`);
        } catch (error: any) {
            throw new Error(`Failed to terminate Database ${this.id}: ${error.message}`);
        }
    }
}