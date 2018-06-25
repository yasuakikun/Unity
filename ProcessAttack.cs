using System.Collections;
using UnityEngine;

public class ProcessAttack : MonoBehaviour {


    private MoveEnemy moveenemy;
    private BoxCollider boxCollider;
    private Animator animator;


    void Start()
    {
        moveenemy = GetComponent<MoveEnemy>();
        boxCollider = GetComponent<BoxCollider>();
        animator = GetComponent<Animator>();
    }

    void Update()
    {
     
    }
}
