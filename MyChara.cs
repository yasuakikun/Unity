using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class MyChara : MonoBehaviour
{

    //キャラクターコントローラー
    private CharacterController cCon;
    private Rigidbody rigidbody;
    //　キャラクターの速度
    private Vector3 velocity;
    //　Animator
    private Animator animator;
    //　歩くスピード
    [SerializeField]
    private float walkSpeed = 3.0f;
    //　走るスピード
    [SerializeField]
    private float runSpeed = 6.0f;
    //　走っているかどうか
    private bool runFlag = false;
    //　通常のジャンプ力
    [SerializeField]
    private float jumpPower = 5f;
    //　走っている時のジャンプ力
    [SerializeField]
    private float dashJumpPower = 5.6f;
    //　キャラクター視点のカメラ
    private Transform myCamera;
    //　カメラのTransform
    [SerializeField]
    private Transform cameraPosition;
    //　キャラクター視点のカメラで回転出来る限度
    [SerializeField]
    private float cameraRotateLimit = 30f;
    //　カメラの上下の移動方法。マウスを上で上を向く場合はtrue、マウスを上で下を向く場合はfalseを設定
    [SerializeField]
    private bool cameraRotForward = true;
    //　カメラの角度の初期値
    private Quaternion initCameraRot;
    //　キャラクター、カメラ（視点）の回転スピード
    [SerializeField]
    private float rotateSpeed = 3f;
    //　カメラのX軸の角度変化値
    private float xRotate;
    //　キャラクターのY軸の角度変化値
    private float yRotate;
    //　マウス移動のスピード
    [SerializeField]
    private float mouseSpeed = 2f;
    //　キャラクターのY軸の角度
    private Quaternion charaRotate;
    //　カメラのX軸の角度
    private Quaternion cameraRotate;
    //　銃を構えているかどうか
    private bool waitShot = false;
    //　キャラクターの脊椎のボーン
    [SerializeField]
    private Transform spine;
    //弾の弾数
    private int numOfBulletsShot = 30;
    //銃を撃った時の処理スクリプト
    //プレイヤーのじょうたい
    private MyState state;


 
    public enum MyState
    {
        Normal,
        Damage
    }

    //private Shot shot;
    void Start()
    {
        //キャラクターコントローラの取得
        cCon = GetComponent<CharacterController>();
        rigidbody = GetComponent<Rigidbody>();
        animator = GetComponent<Animator>();
        myCamera = GetComponentInChildren<Camera>().transform;  //キャラクター視点のカメラの取得
        initCameraRot = myCamera.localRotation;
        charaRotate = transform.localRotation;
        cameraRotate = myCamera.localRotation;
        //shot = GetComponent<Shot>();
        velocity = Vector3.zero;
    }

    //　キャラが回転中かどうか？
    private bool charaRotFlag = false;


    public void TakeDamage(Transform enemyTransform)
    {
        state = MyState.Damage;
        velocity = Vector3.zero;
    }

    public void DamageEnd()
    {
        state = MyState.Normal;
    }



    void Update()
    {
        //　キャラクターの向きを変更する
        RotateChara();
        //　視点の向きを変える
        RotateCamera();

        //　キャラクターコントローラのコライダが地面と接触してるかどうか
        if (cCon.isGrounded)
        {

            velocity = Vector3.zero;

            velocity = (transform.forward * Input.GetAxis("Vertical") * Time.deltaTime + transform.right * Input.GetAxis("Horizontal") * Time.deltaTime).normalized;
            //走るか歩くかでスピードを変更する
            
            float speed = 0f;
            if (Input.GetButton("Run"))
            {
                runFlag = true;
                speed = runSpeed;
            }
            else
            {
                runFlag = false;
                speed = walkSpeed;
            }
            velocity *= speed;

            if (Input.GetButtonDown("Jump"))
            {
                //　走って移動している時はジャンプ力を上げる
                if (runFlag && velocity.magnitude > 0f)
                {
                    velocity.y += dashJumpPower;
                }
                else
                {
                    velocity.y += jumpPower;
                }
            }

            if (velocity.magnitude > 0f)
            {
                if (runFlag && !charaRotFlag)
                {
                    animator.SetFloat("Speed", 6f);
                }
                else
                {
                    animator.SetFloat("Speed", 3f);
                }
            }
            else
            {
                animator.SetFloat("Speed", 0f);
            }
        }

        velocity.y += Physics.gravity.y * Time.deltaTime; //　重力値を計算
        cCon.Move(velocity * walkSpeed * Time.deltaTime); //キャラクターコントローラのMoveを使ってキャラクターを移動させる


        //　銃を構える
        //if (Input.GetButton("Fire2"))
        //{
        //    waitShot = true;
        //    animator.SetBool("WaitShot", true);
        //}
        //else
        //{
        //    waitShot = false;
        //    animator.SetBool("WaitShot", false);
        //}

        //　銃を撃つ
        //if (Input.GetButton("Fire1"))
        //if (waitShot && Input.GetButtonDown("Fire1"))
        //{
        //    //shot.Judge();
        //    animator.SetBool("Shot",true);
        //}
    }
    void LateUpdate()
    {
        //　ボーンをカメラの角度に向かせる
        RotateBone();

        //　カメラの位置と角度を変更
        //myCamera.localRotation = cameraPosition.localRotation;
        //myCamera.position = cameraPosition.position;
    }

    //　キャラクターの角度を変更
    void RotateChara()
    {
        //　横の回転値を計算
        float yRotate = Input.GetAxis("Mouse X") * 2;

        charaRotate *= Quaternion.Euler(0f, yRotate, 0f);

        //　キャラクターが回転しているかどうか？

        if (yRotate != 0f)
        {
            charaRotFlag = true;
        }
        else
        {
            charaRotFlag = false;
        }

        //　キャラクターの回転を実行
        transform.localRotation = Quaternion.Slerp(transform.localRotation, charaRotate, rotateSpeed * Time.deltaTime*200);
    }
    //　カメラの角度を変更
    void RotateCamera()
    {
        float xRotate = Input.GetAxis("Mouse Y") * 2;

        //　マウスを上に移動した時に上を向かせたいなら反対方向に角度を反転させる
        if (cameraRotForward)
        {
            xRotate *= -1;
        }
        //　一旦角度を計算する	
        cameraRotate *= Quaternion.Euler(xRotate, 0f, 0f);
        //　カメラのX軸の角度が限界角度を超えたら限界角度に設定
        //var resultYRot = Mathf.Clamp(Mathf.DeltaAngle(initCameraRot.eulerAngles.x, cameraRotate.eulerAngles.x), -cameraRotateLimit, cameraRotateLimit);
        ////　角度を再構築
        //cameraRotate = Quaternion.Euler(resultYRot, cameraRotate.eulerAngles.y, cameraRotate.eulerAngles.z);
        //　カメラの視点変更を実行
        myCamera.localRotation = Quaternion.Slerp(myCamera.localRotation, cameraRotate, rotateSpeed * Time.deltaTime*200);
        //cameraPosition.localRotation = Quaternion.Slerp(myCamera.localRotation, cameraRotate, rotateSpeed * Time.deltaTime);
    }
    void RotateBone()
    {
        //　腰のボーンの角度をカメラの向きにする
        spine.rotation = Quaternion.Euler(spine.eulerAngles.x, spine.eulerAngles.y, spine.eulerAngles.z + myCamera.localEulerAngles.x);
    }

}