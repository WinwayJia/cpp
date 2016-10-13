-------------------------MySQL-----------------------------------
create database db_user_info;
use db_user_info;
set names utf8;
drop table if exists t_user_info;
create table t_user_info
(
    id          bigint unsigned not null comment 'user id',
    name        varchar(64) not null comment 'user name',
    type        varchar(32) not null comment 'user type',
    primary key (id)
)engine=InnoDB DEFAULT CHARSET=utf8;

drop table if exists t_user_relationship;
create table t_user_relationship
(
    host_id     bigint unsigned not null comment 'host user id, always small id',
    valet_id    bigint unsigned not null comment 'valet user id',
    state       tinyint unsigned not null default 0 comment 'relationship state, 1 - host dont like valet 2 - valet dont like host 4 - host like valet 8 - valet like host',
    primary key (host_id, valet_id),
    index idx_host (host_id),
    index idx_valet (valet_id)
)engine=InnoDB DEFAULT CHARSET=utf8;

/*
    get the two user's relationship
    @aHostID: host id, the vlaue always less than aValetID
    @aValetID: valet id
    return: the relationship
*/
drop procedure if exists pr_get_user_relationship;
delimiter //
create procedure pr_get_user_relationship(aHostID bigint unsigned, aValetID bigint unsigned)
begin 
    select state from t_user_relationship where host_id = aHostID and valet_id = aValetID;
end //
delimiter ;

/*
    save the two user's relationship
    @aHostID: host id, the vlaue always less than aValetID
    @aValetID: valet id
    @aState: the relationship
    retrun 0 - succsss other - fail
*/
drop procedure if exists pr_save_user_relationship;
delimiter //
create procedure pr_save_user_relationship(aHostID bigint unsigned, aValetID bigint unsigned, aState tinyint unsigned, aRet int)
begin
    set aRet = 0;
    update t_user_relationship set state = aState where host_id = aHostID and valet_id = aValetID;
    if (row_count() < 1) then
        insert into t_user_relationship values (aHostID, aValetID, aState);
        if (row_count() < 1) then
            set aRet = 1;
            rollback;
        end if;
    end if;
    
    select aRet;
end //
delimiter ;

------------------PostgresSQL----------------------------------
-- create sequence
create sequence t_user_id_seq increment by 1 minvalue 1 no maxvalue start with 10000000000;

drop table if exists t_user_info;
create table t_user_info
(
    id          bigint not null default nextval('t_user_id_seq'),
    name        varchar(64) not null,
    type        varchar(32) not null,
    primary key (id)
);

/*
*/
--DROP FUNCTION pr_add_new_user(character varying,character varying)
create or replace function pr_add_new_user(aName varchar(64), aType varchar(32)) returns bigint as
$body$
declare user_id bigint;
declare row_count int;
begin
    select nextval('t_user_id_seq') into user_id;
    insert into t_user_info(id, name, type) values (user_id, aName, aType);
    return user_id;
end;
$body$ LANGUAGE plpgsql;

drop table if exists t_user_relationship;
create table t_user_relationship
(
    user_id     bigint not null,
    relationship json,
    primary key(user_id)
);


select json_object('{id, id, name, name, type, type}') from t_user_info;
