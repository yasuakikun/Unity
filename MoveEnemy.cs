using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MoveEnemy : MonoBehaviour
{

    private CharacterController enemyController;
    private Animator animator;
    //　目的地
    private Vector3 destination;
    //　歩くスピード
    [SerializeField]
    private float walkSpeed = 1.0f;
    //　速度
    private Vector3 velocity;
    //　移動方向
    private Vector3 direction;
    //　到着フラグ
    private bool arrived;
    //　敵の初期位置スクリプト
    private EnemySetPos setPosition;
    //　待ち時間
    [SerializeField]
    private float waitTime = 5f;
    //　経過時間
    private float ProgressTime;
    private EnemyState state;
    private Transform playerTransform;
    [SerializeField]
    private float freezetime = 0.3f;
    //敵のマックスHP
    private int MaxHp = 100;
    //敵のHP
    private int HP;
    //ゾンビのアタックダメージ,
     int ZombieDamage = 10;
    //ダメージを受けたかどうか
    private bool DamageCheck;



    public enum EnemyState
    {
        Walk,
        Wait,
        Chase,
        Attack,
        Freeze,
        Dead
    };

    //敵の状態変更
    public void SetState(string mode, Transform obj = null)
    {
        if (mode == "Walk")
        {
            arrived = false;
            ProgressTime = 0f;
            state = EnemyState.Walk;
            setPosition.CreateRandomPosition();
            animator.SetBool("Attack", false);
        }
        else if (mode == "chase")
        {
            state = EnemyState.Chase;
            //　待機状態から追いかける場合もあるのでOff
            arrived = false;
            //　追いかける対象をセット
            playerTransform = obj;
        }
        else if (mode == "wait")
        {
            ProgressTime = 0f;
            state = EnemyState.Wait;
            arrived = true;
            velocity = Vector3.zero;
            animator.SetFloat("Speed", 0f);
            animator.SetBool("Attack", false);
        }
        else if (mode == "attack")
        {
            ProgressTime = 0f;
            state = EnemyState.Attack;
            arrived = true;
            velocity = Vector3.zero;
            animator.SetFloat("Speed", 0f);
            animator.SetBool("Attack", true);
        }
        else if (mode == "freeze")
        {
            ProgressTime = 0f;
            arrived = true;
            state = EnemyState.Freeze;
            velocity = Vector3.zero;
            animator.SetFloat("Speed", 0f);
            animator.SetBool("Attack", false);
        }
        else if (mode == "dead")
        {
            ProgressTime = 0f;
            arrived = true;
            state = EnemyState.Dead;
            velocity = Vector3.zero;
            animator.SetFloat("Speed", 0f);
            animator.SetBool("Dead", true);
        }
    }

    public EnemyState GetState()
    {
        return state;
    }

    //　ダメージ値を追加するメソッド
    public void OnDamage(int damage)
    {
        HP -= damage;
    }

    public int GetHp()
    {
        return HP;
    }
    public int GetMaxHp()
    {
        return MaxHp;
    }
    // Use this for initialization
    public void ZombieOnDamage(int ZombieDamage)
    {
        HP -= ZombieDamage;
    }
    void Start()
    {
        enemyController = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
        setPosition = GetComponent<EnemySetPos>();
        setPosition.CreateRandomPosition();
        velocity = Vector3.zero;
        arrived = false;
        DamageCheck = false;
        //経過時間０
        ProgressTime = 0f;
        //最初のステート
        SetState("wait");
        //hpmax
        HP = MaxHp;
    }

    // Update is called once per frame
    void Update()
    {
        //　見回りまたはキャラを追尾する状態
        if (state == EnemyState.Walk || state == EnemyState.Chase)
        {
            //　キャラクターを追いかける状態であればキャラクターの目的地を再設定
            if (state == EnemyState.Chase)
            {
                setPosition.SetDestination(playerTransform.position);
            }
            if (enemyController.isGrounded)
            {
                velocity = Vector3.zero;
                animator.SetFloat("Speed", 2.0f);
                direction = (setPosition.GetDestination() - transform.position).normalized;
                transform.LookAt(new Vector3(setPosition.GetDestination().x, transform.position.y, setPosition.GetDestination().z));
                velocity = direction * walkSpeed;
            }
            if (state == EnemyState.Walk)
            {
                //　目的地に到着したかどうかの判定
                if (Vector3.Distance(transform.position, setPosition.GetDestination()) < 0.7f)
                {
                    SetState("wait");
                    animator.SetFloat("Speed", 0.0f);
                }
            }
            else if (state == EnemyState.Chase)
            {
                if (Vector3.Distance(transform.position, setPosition.GetDestination()) < 1.0f)
                {
                    SetState("attack");
                    animator.SetBool("Attack", true);
                }
            }
        }


        //　到着していたら一定時間待つ
        else if (state == EnemyState.Wait)
        {
            ProgressTime += Time.deltaTime;
            //　待ち時間を越えたら次の目的地を設定
            if (ProgressTime > waitTime)
            {
                SetState("Walk");
            }
        }
        else if (state == EnemyState.Freeze)
        {
            ProgressTime += Time.deltaTime;
            //　待ち時間を越えたら次の目的地を設定
            if (ProgressTime > freezetime)
            {
                SetState("Walk");
            }
        }

        //ダメージが入っていないときリターンする
        if (DamageCheck == false)
        {
            return;
        }
        //ダメージが入ってるとき
        if (DamageCheck == true)
        {
            ////ダメージ量
            //var GetDamage = onDamage / 5;
            //if (GetDamage == 0)
            //{
            //    GetDamage = onDamage % 10;
            //}
            //HP -= GetDamage;
            //onDamage -= GetDamage;

            //敵のHPが半分になったら、ダメージアニメーション
            //if(HP <= 50)
            //{
            //    SetState("demage");
            //    animator.SetBool("Damage", true);
            //}


            //敵のHPが０になったら死亡アニメーション

            if (HP <= 0)
            {
                SetState("dead");
                animator.SetBool("Dead", true);
               Destroy(gameObject);
            }
        }
        velocity.y += Physics.gravity.y * Time.deltaTime;
        enemyController.Move(velocity * Time.deltaTime);
    }
}

