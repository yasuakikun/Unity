using UnityEngine;
using System.Collections;

public class HandIK : MonoBehaviour
{

    //　左手の位置
    [SerializeField]
    private Transform leftHand;
    private Animator animator;

    void Start()
    {
        animator = GetComponent<Animator>();
    }

    void OnAnimatorIK()
    {
        //　キャラクターの左手の位置と角度を合わせる

        animator.SetIKPositionWeight(AvatarIKGoal.LeftHand, 1);
        animator.SetIKRotationWeight(AvatarIKGoal.LeftHand, 1);

        animator.SetIKPosition(AvatarIKGoal.LeftHand, leftHand.position);
        animator.SetIKRotation(AvatarIKGoal.LeftHand, leftHand.rotation);

    }
}
